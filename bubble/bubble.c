#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <winbase.h>
#include <psapi.h>

double get_memory_used_MB()
{
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (double)info.PeakWorkingSetSize/ (1024*1024);
}


void bubble_sort (int vetor[], int n) {
    int k, j, aux;

    for (k = 1; k < n; k++) {
        //printf("\n[%d] ", k);

        for (j = 0; j < n - 1; j++) {
            //printf("%d, ", j);

            if (vetor[j] > vetor[j + 1]) {
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void montarGrafico(float tempo[],float memoria[], int qtd[],char nomedesaida, int id,int N){
    FILE *web;
    if(id==1){
        web = fopen("grafico-Ordenado.html", "w+");
    }else if(id == 2){
        web = fopen("grafico-aleatorio.html", "w+");
    }else{
        web = fopen("grafico-Decrescente.html", "w+");
    }

      if (web == NULL)
      {
         printf("Problemas na CRIACAO do arquivo html\n");
      }
    fprintf(web,"<!DOCTYPE html><html lang='pt-br'> <head> <meta charset='utf-8'/> <title>Graficos Bolha</title><script src='https://www.chartjs.org/dist/2.9.4/Chart.min.js'></script><script src='https://www.chartjs.org/samples/latest/utils.js'></script> </head> <body></script>");
    fprintf(web,"<div style='width:75%;'><canvas id='canvas%d'></canvas></div>",id);
    fprintf(web,"<script>var lineChartData%d={labels: [2000,4000,8000,16000,32000,64000,128000],datasets: [{label: 'Tempo',borderColor: window.chartColors.red,backgroundColor: window.chartColors.red,fill: false,data: [",id);
    for(int i =0; i<N;i++){
        if(i==(N-1)){
            fprintf(web,"%f",tempo[i]);
        }else{
            fprintf(web,"%f,",tempo[i]);
        }
    }
    fprintf(web,"],yAxisID: 'y-axis-1',},{label: 'Memoria',borderColor: window.chartColors.blue,backgroundColor: window.chartColors.blue,fill: false,data: [");
    for(int i =0; i<N;i++){
        if(i==(N-1)){
            fprintf(web,"%f",memoria[i]);
        }else{
            fprintf(web,"%f,",memoria[i]);
        }
    }
    fprintf(web,"],yAxisID: 'y-axis-2'}]};window.onload=function(){var ctx%d=document.getElementById('canvas%d').getContext('2d');window.myLine=Chart.Line(ctx%d,{data: lineChartData%d,options:{responsive: true,hoverMode: 'index',stacked: false,title:{display: true,text: 'Grafico'},scales:{yAxes: [{type: 'linear',display: true,position: 'left',id: 'y-axis-1',},{type: 'linear', display: true,position: 'right',id: 'y-axis-2',gridLines:{drawOnChartArea: false,},}],}}});};</script>",id,id,id,id);
    fprintf(web,"</body></html>");
    fclose(web);
}


int main()
{
    int n[7];
    n[0] = 2000;
    n[1] = 4000;
    n[2] = 8000;
    n[3] = 16000;
    n[4] = 32000;
    n[5] = 64000;
    n[6] = 128000;
    float Tordenado[3][7];
    float Taleatorio[3][7];
    float Tdesordenado[3][7];
    float Mordenado[3][7];
    float Maleatorio[3][7];
    float Mdesordenado[3][3];


    FILE *arq;
      arq = fopen("Data-Bubble.csv", "w+");
      if (arq == NULL)
      {
         printf("Problemas na CRIACAO do arquivo\n");
         return;
      }
      fprintf(arq,"TAMANHO,TEMPO,MEMORIA,DADOS\n");

    for(int j =0;j<7;j++){
    int N = n[j];
    int vet[N];

    clock_t start_time, end_time;
    double cpu_time_used, memory_used;
    size_t peakSize;







    //Ordenado
    printf("\n\n\nVetor ORDENADO - MELHOR CASO\n");
    for(int i =0; i <N;i++){
        vet[i] = i;
    }


    start_time = clock();


    bubble_sort(vet,N);




     end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    memory_used = get_memory_used_MB();

    printf("\n\n TESTE COM %d \n  Tempo: %0.2f segundos - Memoria: %0.2f MB\n",n[j],cpu_time_used, memory_used);
    Tordenado[0][j] = cpu_time_used;
    Mordenado[0][j] = memory_used;
    fprintf(arq,"%d,%f,%f,ORDENADO\n",n[j],cpu_time_used, memory_used);


    //ALEATÓRIO
    printf("Vetor ALEATÓRIO - CASO MÉDIO");
    for(int i =0; i <N;i++){
        vet[i] =  (rand() % N);
    }


    start_time = clock();


    bubble_sort(vet,N);




     end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    memory_used = get_memory_used_MB();

    printf("\n\n TESTE COM %d \n  Tempo: %0.2f segundos - Memoria: %0.2f MB\n",n[j],cpu_time_used, memory_used);
    fprintf(arq,"%d,%f,%f,ALEATORIO\n",n[j],cpu_time_used, memory_used);
    Taleatorio[1][j] = cpu_time_used;
    Maleatorio[1][j] = memory_used;




    //DESORDENADO
    printf("Vetor DESORDENADO - PIOR CASO");
    for(int i =0; i <N;i++){
        vet[i] =  N-i;
    }

    start_time = clock();


    bubble_sort(vet,N);




     end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    memory_used = get_memory_used_MB();

    printf("\n\n TESTE COM %d \n  Tempo: %0.2f segundos - Memoria: %0.2f MB\n",n[j],cpu_time_used, memory_used);
    fprintf(arq,"%d,%f,%f,DECRESCENTE\n",n[j],cpu_time_used, memory_used);
    Tdesordenado[2][j] = cpu_time_used;
    Mdesordenado[2][j] = memory_used;

    }
    montarGrafico(Tordenado[0],Mordenado[0],n,"grafico-ordenado.html",1,7);
    montarGrafico(Taleatorio[1],Maleatorio[1],n,"grafico-aleatorio.html",2,7);
    montarGrafico(Tdesordenado[2],Mdesordenado[2],n,"grafico-decresdente",3,7);
    fclose(arq);
    printf("\n\n\a GRAFICOS GERADOS COM SUCESSO!!\n verifique a pasta do programa para ver os graficos no navegador web.");
    return 0;
}
