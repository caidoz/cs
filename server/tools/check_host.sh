#!/bin/sh
# 서버에 서비스를 올릴 준비가 됐는지 본다.
#
# 읽기만 한다. 설치도 변경도 하지 않는다. 그래서 아무 서버에서나
# 마음 놓고 돌려도 된다.
#
#   sh check_host.sh
#
# 무엇을 왜 보는지는 server/PLAN 문서의 "단계" 절과 짝이다.

say() { printf '%-14s %-10s %s\n' "$1" "$2" "$3"; }
ok()   { say "$1" "있음" "$2"; }
no()   { say "$1" "없음" "$2"; }
warn() { say "$1" "확인"  "$2"; }

has() { command -v "$1" >/dev/null 2>&1; }

echo "=============================================================="
echo " 호스트"
echo "=============================================================="
. /etc/os-release 2>/dev/null
say "배포판" "" "${PRETTY_NAME:-알 수 없음} ($(uname -m))"
say "커널"   "" "$(uname -r)"
say "메모리" "" "$(free -h 2>/dev/null | awk '/^Mem:/{print $2" 중 "$7" 여유"}')"
say "디스크" "" "$(df -h / 2>/dev/null | awk 'NR==2{print $2" 중 "$4" 여유"}')"
say "시각"   "" "$(date -u '+%Y-%m-%d %H:%M:%S UTC')  TZ=$(cat /etc/timezone 2>/dev/null || readlink /etc/localtime | sed 's|.*zoneinfo/||')"

echo
echo "=============================================================="
echo " 반드시 필요한 것"
echo "=============================================================="

# ---- DB : 스키마가 MariaDB 10.6+ 를 전제로 쓰였다 -------------------
if has mariadbd || has mysqld; then
    v=$( (mariadbd --version 2>/dev/null || mysqld --version 2>/dev/null) | head -1 )
    ok "MariaDB" "$v"
elif has mariadb || has mysql; then
    v=$( (mariadb --version 2>/dev/null || mysql --version 2>/dev/null) | head -1 )
    warn "MariaDB" "클라이언트만 있다 : $v"
else
    no "MariaDB" "서버 본체가 없다. 10.6 이상이 필요하다"
fi

# ---- 웹 종단 : TLS 를 끊고 게임 서버로 넘긴다 -----------------------
if has nginx; then ok "nginx" "$(nginx -v 2>&1)"
elif has caddy; then ok "caddy" "$(caddy version 2>/dev/null | head -1)"
elif has httpd || has apache2; then warn "웹서버" "apache 가 있다. nginx 를 권한다"
else no "nginx" "TLS 종단이 없다"; fi

# ---- 인증서 ---------------------------------------------------------
if has certbot; then ok "certbot" "$(certbot --version 2>&1)"
elif has caddy; then ok "인증서" "caddy 가 자동으로 한다"
else no "certbot" "Let's Encrypt 발급 도구가 없다"; fi

# ---- 서비스 관리 ----------------------------------------------------
if has systemctl; then ok "systemd" "$(systemctl --version | head -1)"
else no "systemd" "서비스 등록 방법을 따로 정해야 한다"; fi

# ---- 시계 : 서버가 #now 를 주므로 이게 틀리면 전부 틀린다 -----------
if has timedatectl; then
    s=$(timedatectl show -p NTPSynchronized --value 2>/dev/null)
    [ "$s" = "yes" ] && ok "시각동기화" "NTP 맞춰져 있다" || warn "시각동기화" "NTP 가 안 맞는다. 하트회복/일일보상이 이 시계 위에 선다"
elif has chronyc; then ok "시각동기화" "chrony"
else warn "시각동기화" "확인 불가. 반드시 켜야 한다"; fi

echo
echo "=============================================================="
echo " 서버 언어 (둘 중 하나만 고르면 된다)"
echo "=============================================================="
if has go; then ok "Go" "$(go version)"; else no "Go" "권고안. 단일 정적 바이너리로 배포된다"; fi
if has python3; then
    ok "Python3" "$(python3 --version 2>&1)"
    python3 -c 'import venv' 2>/dev/null && ok "  venv" "쓸 수 있다" || no "  venv" "python3-venv 가 따로 필요하다"
else no "Python3" "대안. tools/ 가 이미 파이썬이다"; fi

echo
echo "=============================================================="
echo " 0단계(로컬 DB 세우기)에 쓰는 것"
echo "=============================================================="
if has docker; then
    ok "docker" "$(docker --version 2>&1)"
    docker compose version >/dev/null 2>&1 && ok "  compose" "$(docker compose version 2>&1 | head -1)" \
        || { has docker-compose && ok "  compose" "$(docker-compose --version 2>&1)" || no "  compose" "플러그인이 없다"; }
else no "docker" "없어도 된다. DB 를 직접 깔면 그만이다"; fi

echo
echo "=============================================================="
echo " 있으면 편한 것"
echo "=============================================================="
for c in git curl rsync unzip tar logrotate fail2ban-client; do
    has "$c" && ok "$c" "" || no "$c" ""
done

echo
echo "=============================================================="
echo " 방화벽과 열린 포트"
echo "=============================================================="
if has ufw; then say "ufw" "" "$(ufw status 2>/dev/null | head -1)"
elif has firewall-cmd; then say "firewalld" "" "$(firewall-cmd --state 2>/dev/null)"
else say "방화벽" "" "ufw/firewalld 둘 다 없다"; fi

echo "-- 지금 듣고 있는 포트 --"
if has ss; then ss -lntp 2>/dev/null | awk 'NR==1 || /:(22|80|443|3306|8080)\>/'
elif has netstat; then netstat -lntp 2>/dev/null | head -20
else echo "ss/netstat 이 없다"; fi

echo
echo "=============================================================="
echo " DB 가 이미 돌고 있다면"
echo "=============================================================="
if has mariadb || has mysql; then
    cli=$(command -v mariadb || command -v mysql)
    if "$cli" -N -B -e "SELECT VERSION()" 2>/dev/null; then
        echo "-- 접속됨. 아래는 스키마가 요구하는 것들 --"
        "$cli" -N -B -e "SELECT CONCAT('  charset  ', @@character_set_server, ' / ', @@collation_server)" 2>/dev/null
        "$cli" -N -B -e "SELECT CONCAT('  innodb   ', IF(@@default_storage_engine='InnoDB','OK', @@default_storage_engine))" 2>/dev/null
        "$cli" -N -B -e "SELECT CONCAT('  binlog   ', @@log_bin)" 2>/dev/null
        "$cli" -N -B -e "SELECT CONCAT('  DB목록   ', GROUP_CONCAT(schema_name)) FROM information_schema.schemata" 2>/dev/null
    else
        echo "  접속 못 했다(비밀번호가 필요하거나 안 돌고 있다)"
    fi
fi

echo
echo "점검 끝. 아무것도 바꾸지 않았다."
