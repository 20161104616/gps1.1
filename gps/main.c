#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, const char* argv[])
{
    char a[100];
    char b[100];
    char lat[9],lon[9],spe[6],course[6],days[7],time[7], satellite[3],altituden[5];//纬度 经度 速度 航向 日期 时间 卫星 海拔
    FILE *fr,*fw;
    int i;
    int numbig,numsm,year,month,day,hour,minute,second;//转换变量
    double speed;
    fr = fopen("//Users//a20161104616//Desktop//gps-master//gps//GPS170510.log", "r+");
    if(fr==NULL)
    {
        printf("fr文件打开失败\n");
    }
    fw = fopen("//Users//a20161104616//Desktop//gps-master//gps//GPS.csv", "w+");
    if(fw==NULL)
    {
        printf("fw文件打开失败\n");
    }
    
    fprintf(fw,"纬度(N),经度(E),速度(km/h),航向,时间,日期,卫星数量,海拔高度\n");
    while(!feof(fr))
    {
        fscanf(fr, "%s%s",a,b);
        printf("%s\n%s\n",a,b);
        
        for(i = 0;i < 8;i++)
        {
            lat[i] = a[i+16];
        }
        lat[8] = '\0';
        printf("纬度：%s\n",lat);
        fprintf(fw,"%s,",lat);
        
        for(i = 0;i < 8;i++)
        {
            lon[i] = a[i+27];
        }
        lon[8] = '\0';
        printf("经度：%s\n",lon);
        fprintf(fw,"%s,",lon);
        
        for(i = 0;i < 6;i++)
        {
            spe[i] = a[i+39];
        }
        spe[5]='\0';
        speed = atoi(spe);
        speed = speed*1.852;
        printf("速度（km／h）:%.2lf\n",speed);
        fprintf(fw,"%lf,",speed);
        
        for(i = 0;i < 6;i++)
        {
            course[i] = a[i+45];
        }
        course[5] = '\0';
        printf("航向:%s\n",course);
        fprintf(fw,"%s,",course);
        
        for(i = 0;i < 8;i++)
        {
            time[i] = a[i+7];
        }
        time[6]='\0';
        numsm  = atoi(time);
        second = numsm%100;
        minute = (numsm/100)%100;
        hour   = numsm/10000+8;
        if(hour>=24)
        {
            hour = hour-23;
        }
        printf("%d时%d分%d秒,",hour,minute,second);
        fprintf(fw,"%d时%d分%d秒,",hour,minute,second);
        
        for(i = 0;i < 6;i++)
        {
            days[i] = a[i+51];
        }
        days[6]='\0';
        numbig = atoi(days);
        year   = numbig%100;
        month  = (numbig/100)-1000;
        day    = ((numbig/100)-month)/100;
        printf("%d年%d月%d日,",year,month,day);
        fprintf(fw,"%d年%d月%d日,",year,month,day);
        
        for(i = 0;i < 3;i++)
        {
            satellite[i] = b[i+39];
        }
        satellite[2] = '\0';
        printf("卫星数量:%s\n",satellite);
        fprintf(fw,"%s,",satellite);
        
        for(i = 0;i < 5;i++)
        {
            altituden[i] = b[i+43];
        }
        altituden[4] = '\0';
        printf("海拔高度%s\n",altituden);
        fprintf(fw,"%s\n",altituden);
        
    }
    fclose(fw);
    fclose(fr);
    return 0;
}
