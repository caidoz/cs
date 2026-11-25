#pragma once
#include <string>
// Stable legacy IDs are preserved; each event now resolves to one authored flat asset.
inline std::string GameSfxPath(int id){
 static const char* names[49]={
  "sfx-roulette-spin.ogg",
  "sfx-rest-confirm.ogg",
  "sfx-text-tick.ogg",
  "sfx-footstep.ogg",
  "sfx-blade-swing.ogg",
  "sfx-blade-heavy.ogg",
  "sfx-gun-shot.ogg",
  "sfx-cannon-blast.ogg",
  "sfx-boomerang-throw.ogg",
  "sfx-boomerang-spin.ogg",
  "sfx-blade-hit.ogg",
  "sfx-projectile-hit.ogg",
  "sfx-boomerang-hit.ogg",
  "sfx-reload.ogg",
  "sfx-laser-beam.ogg",
  "sfx-fire-burst.ogg",
  "sfx-buff-heal.ogg",
  "sfx-buff-haste.ogg",
  "sfx-buff-mana.ogg",
  "sfx-buff-power.ogg",
  "sfx-explosion.ogg",
  "sfx-monster-death.ogg",
  "sfx-ground-impact.ogg",
  "sfx-door-open.ogg",
  "sfx-item-pickup.ogg",
  "sfx-level-up.ogg",
  "sfx-tile-land.ogg",
  "sfx-reward-good.ogg",
  "sfx-reward-perfect.ogg",
  "sfx-heartbeat.ogg",
  "sfx-coin-drop.ogg",
  "sfx-menu-navigate.ogg",
  "sfx-ui-denied.ogg",
  "sfx-ui-click.ogg",
  "sfx-jump.ogg",
  "sfx-item-unlock.ogg",
  "sfx-monster-summon.ogg",
  "sfx-machine-gear.ogg",
  "sfx-metal-clang.ogg",
  "sfx-panel-open.ogg",
  "sfx-panel-close.ogg",
  "sfx-upgrade.ogg",
  "sfx-laser-charge.ogg",
  "sfx-card-reveal.ogg",
  "sfx-victory.ogg",
  "sfx-purchase.ogg",
  "sfx-alarm.ogg",
  "sfx-ui-drag.ogg",
  "sfx-ui-shake.ogg",
 };
 return id>=23&&id<72?std::string("res/")+names[id-23]:std::string();
}
bool DispatchGameSfx(int id);
int GameSfxPlayedCount();
int GameSfxSuppressedCount();
int GameSfxActiveCount();
void StopGameSfx();
