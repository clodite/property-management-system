
#define BasicYear 2000 //����ȫ����ʱ��������õĻ�׼ʱ��ĺ� 
#define BasicMonth 3
#define BasicDay 14
#define BasicHour 0

int Lpday[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31}; //ʱ����õ� ���������ƽ������ 
int Coday[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

struct time
{
	int year;
	int month;
	int day;
	int hour; 
};

int time_to_timestamp(struct time Intime)
{
	int timestamp = 0;
	int trans = 0;
	int trans1 = 0;
	struct time Bstime;
	Bstime.year = BasicYear; //��һ��Ľṹ�� 
	Bstime.month = BasicMonth;
    Bstime.day = BasicDay;
    Bstime.hour = BasicHour;
    trans = Count_BasicYear(Bstime);
    trans1 = Count_EndYear(Intime);
    trans = trans1 + trans;
    trans1 = 0;
    int i = Bstime.year + 1;
    for(i=Bstime.year + 1; i<=Intime.year-1 ; i++) //�ж��м��������; 
    {
    	trans1 = trans1  + 365 + JudgeYear(i);
	}
    trans = trans + trans1;
    trans = 24 * trans;
	trans = trans - Bstime.hour + Intime.hour;
	timestamp = trans;
	return trans;
}

int Count_BasicYear(struct time time1) //����ʱ����������õĵ�һ��������ж� 
{
	int result = 0;
	int n = JudgeYear(time1.year);
	if(n==1)
	{
        int i = time1.month;
        for(i=time1.month ; i<=12; i++)
        {
        	result = result + Lpday[i];
		}
		result = result - time1.day + 1;
	}
	else if(n==0)
	{
        int i = time1.month;
        for(i=time1.month ; i<=12; i++)
        {
        	result = result + Coday[i];
		}
		result = result - time1.day + 1;
	}
	return result;
}

int Count_EndYear(struct time time1) //����ʱ����������õ����һ��������ж� 
{
	int result = 0;
	int n = JudgeYear(time1.year);
	if(n==1)
	{
        int i = time1.month - 1;
        for(i=time1.month - 1 ; i>=1; i--)
        {
        	result = result + Lpday[i];
		}
		result = result + time1.day - 1;
	}
	else if(n==0)
	{
        int i = time1.month - 1;
        for(i=time1.month - 1 ; i>=1; i--)
        {
        	result = result + Coday[i];
		}
		result = result + time1.day - 1;
	}
	return result;
}


int JudgeYear(int x) //�ж��Ƿ����꣬���귵��1������0 
{
	if(x%4==0 && x%100!=0 || x%400==0)
	   return 1;
	else
	   return 0;
}
