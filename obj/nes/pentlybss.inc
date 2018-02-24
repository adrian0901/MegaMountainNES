; Variables not needed per configuration
; arpPhase (PER_CHANNEL, 4 rows): ARPEGGIO, ATTACK_TRACK disabled
; arpIntervalA (PER_PITCHED_CHANNEL, 4 rows): ARPEGGIO disabled
; arpIntervalB (PER_PITCHED_CHANNEL, 4 rows): ARPEGGIO disabled
; vibratoDepth (PER_PITCHED_CHANNEL, 4 rows): VIBRATO disabled
; vibratoPhase (PER_PITCHED_CHANNEL, 4 rows): VIBRATO disabled
; notePitch (PER_PITCHED_CHANNEL, 4 rows): PORTAMENTO disabled
; chPitchLo (PER_PITCHED_CHANNEL, 4 rows): PORTAMENTO disabled
; chPortamento (PER_PITCHED_CHANNEL, 4 rows): PORTAMENTO disabled
; attackPitch (PER_CHANNEL, 4 rows): ATTACK_TRACK disabled
; pently_rows_per_beat (SINGLETON, 1 row): BPMMATH disabled
; pently_row_beat_part (SINGLETON, 1 row): BPMMATH disabled
; pently_vis_dutyvol (PER_CHANNEL, 4 rows): VIS disabled
; pently_vis_pitchlo (PER_CHANNEL, 4 rows): VIS disabled
; pently_vis_pitchhi (PER_CHANNEL, 4 rows): VIS disabled
; pently_rowshi (PER_CHANNEL, 4 rows): REHEARSAL disabled
; pently_rowslo (PER_CHANNEL, 4 rows): REHEARSAL disabled
; pently_tempo_scale (SINGLETON, 1 row): REHEARSAL disabled
; Columns are 11-12 rows tall, total 47
; Below max: 1; layout waste 0
pentlymusicbase_size = 47
chPitchHi = pentlymusicbase + 0
channelVolume = pentlymusicbase + 16
musicPattern = pentlymusicbase + 32
attack_remainlen = pentlymusicbase + 1
noteRowsLeft = pentlymusicbase + 17
patternTranspose = pentlymusicbase + 33
noteEnvVol = pentlymusicbase + 2
graceTime = pentlymusicbase + 18
pently_mute_track = pentlymusicbase + 34
noteLegato = pentlymusicbase + 3
noteInstrument = pentlymusicbase + 19
music_tempoLo = pentlymusicbase + 35
music_tempoHi = pentlymusicbase + 39
conductorWaitRows = pentlymusicbase + 43
