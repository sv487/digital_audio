#include<stdio.h>
#include<stdint.h>
#include<math.h>
#include<stdlib.h>

// #define sample_rate 44100   // this many samples will be generated for 1 second and save them on a file and feed to a audio player ( 2 bytes) since human hearing is 20000 hz so double of that for oscilating frequency
#define bit_depth 16
#define pie 3.1415

int main(){
    int max_value_encoding = 32767;
    float sample_rate = 44100.0f;
    printf("enter frequency (eg 440 Hz for an A note) duration(seconds) and amplitude(volume)\n");
    float freq , dur , amp;    // 440 hz means 440 oscilations are gonna happen
    scanf("%f %f %f",&freq , &dur,&amp);
    float time;           // each sample would be of 2 bytes , 16 bit encoding scheme
    float sineee = 0;
    long long total_samples = dur * sample_rate;   // gonna use this in for loop to calculate i which is the counter which will give number of samples 

    FILE *f;
    f = fopen("sine.raw","wb");
    if(f == NULL){
        printf("allocation failed , no point in going forward since file not going to be created anyway");
        return -1;
    }

    for(int i=0;i<total_samples;i++){
        time = i/sample_rate;           // 1/44100 is this much time i am gonna spend on one sample
        sineee = 2*pie*freq*time;   
        short int sample = sin(sineee) * max_value_encoding;   // a float value will be generated for each amplitude now which 16 bit number its correspond to so divide the whole wave into 2^16 levels which will be 2^15 in each half which is 32768
       fwrite(&sample,2,1,f);  // telling it where to copy and how many bytes to copy and how many 2 bytes chunk you need to write for that its 1 and what file do u wanna write this stuff

       printf("%d ",sample);   // ok data is generated now just i have to write this into a file

}
}