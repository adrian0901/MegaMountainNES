.include "pently.inc"

.export _Reset_Music, _Play_Music, _Music_Update, _Play_Fx
.export _Mute_Pulse, _Unmute_Pulse

_Reset_Music = pently_init
_Play_Music = pently_start_music
_Music_Update = pently_update
_Play_Fx = pently_start_sound

.proc _Mute_Pulse
  lda #$FF
  sta pently_mute_track+0
  sta pently_mute_track+4
  rts
.endproc

.proc _Unmute_Pulse
  lda #$00
  sta pently_mute_track+0
  sta pently_mute_track+4
  rts
.endproc
