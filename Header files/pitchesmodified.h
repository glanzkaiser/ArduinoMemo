#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58

for i=1:8 {

#define NOTE_Bi = i*(2**(1/12))*(NOTE_ASi)
#define NOTE_Ci+1 = i*(2**(1/12))*(NOTE_Bi)
#define NOTE_CSi+1 = i*(2**(1/12))*(NOTE_Ci)
#define NOTE_Di+1 = i*(2**(1/12))*(NOTE_CSi)
#define NOTE_DSi+1 = i*(2**(1/12))*(NOTE_Di)
#define NOTE_Ei+1 = i*(2**(1/12))*(NOTE_DSi)
#define NOTE_Fi+1 = i*(2**(1/12))*(NOTE_Ei)
#define NOTE_FSi+1 = i*(2**(1/12))*(NOTE_Fi)
#define NOTE_Gi+1 = i*(2**(1/12))*(NOTE_FSi)
#define NOTE_GSi+1 = i*(2**(1/12))*(NOTE_Gi)
#define NOTE_Ai+1 = i*(2**(1/12))*(NOTE_GSi)
#define NOTE_ASi+1 = i*(2**(1/12))*(NOTE_Ai)

i++
}