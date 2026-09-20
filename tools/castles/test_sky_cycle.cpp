#include "../../Classes/LobbySkyCycle.h"
#include "../../Classes/LobbyParallax.h"
#include <cassert>
#include <cstdio>
int main() {
    using namespace LobbySkyCycle;
    assert(hour(0)==9 && hour(300)==9 && hour(150)==21);
    assert(sample(12).night==0 && sample(0).night==1);
    for(int i=0;i<24000;++i) {
        auto a=sample(i*.001), b=sample(i*.001+.001);
        assert(a.night>=0 && a.night<=1);
        assert(std::abs(a.top.r-b.top.r)<.2f);
        assert(std::abs(a.horizon.b-b.horizon.b)<.2f);
    }
    auto a=sample(23.999999),b=sample(0);
    assert(std::abs(a.top.r-b.top.r)<.001f);
    const float zooms[] = {.5f, 1.f, 2.f};
    for (float z : zooms) {
        const float far = LobbyParallax::scale(z, LobbyParallax::Far);
        const float near = LobbyParallax::scale(z, LobbyParallax::Near);
        assert(far > 0 && near > 0);
        assert(std::abs(far - 1) <= std::abs(near - 1));
        // Coverage after the largest allowed horizontal offset.
        assert(1.4f * far / 2 - .08f >= .5f);
        assert(1.6f * near / 2 - .16f >= .5f);
    }
    assert(LobbyParallax::offset(100, LobbyParallax::Far, 80) == 6);
    assert(LobbyParallax::offset(100, LobbyParallax::Near, 160) == 20);
    assert(LobbyParallax::offset(10000, LobbyParallax::Near, 160) == 160);
    assert(LobbyParallax::offset(-10000, LobbyParallax::Near, 160) == -160);
    puts("PASS: five-minute cycle, day/night endpoints, continuous palette and midnight wrap");
}
