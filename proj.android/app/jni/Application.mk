APP_STL := c++_static

APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -std=c++14 -fsigned-char -Wno-extern-c-compat
# 16KB 페이지 정렬: Play 는 targetSdk 35 앱에 요구한다 (NDK r28 부터는 기본값).
APP_LDFLAGS := -latomic -Wl,-z,max-page-size=16384

APP_ABI := arm64-v8a
APP_SHORT_COMMANDS := true


ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif
