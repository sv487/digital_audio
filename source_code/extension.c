#include<stdio.h>
#include<stdint.h>
#include<math.h>
#include<stdlib.h>

#define bit_depth 16
#define pie 3.1415

int main(){
    int max_value_encoding = 32767;
    float sample_rate = 44100.0f;

    printf("how many waves to mix\n");

    int waves;
    scanf("%d",&waves);

    float freq[waves];   // store multiple frequencies

    printf("enter the frequencies\n");
    for(int i=0;i<waves;i++){
        scanf("%f",&freq[i]);
    }

    float dur , amp;
    printf("enter duration(seconds) and amplitude(volume)\n");
    scanf("%f %f",&dur,&amp);

    float time;
    float sineee = 0;

    long long total_samples = dur * sample_rate;

    FILE *f;
    f = fopen("mixed.raw","wb");

    if(f == NULL){
        printf("allocation failed , no point in going forward since file not going to be created anyway");
        return -1;
    }

    for(int i=0;i<total_samples;i++){

        time = i/sample_rate;

        float mixed_wave = 0;

        for(int j=0;j<waves;j++){
            sineee = 2*pie*freq[j]*time;
            mixed_wave += sin(sineee);   // add waves
        }

        mixed_wave = mixed_wave / waves;  // normalization

        short int sample = mixed_wave * amp * max_value_encoding;

        fwrite(&sample,2,1,f);

        printf("%d ",sample);
    }

    fclose(f);
}