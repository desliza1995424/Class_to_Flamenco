//note最小長度
//在fitness放入小節概念(讓重音對應到harmony note上甚至是root of harmony)
//128p 150g -> 16.5sec
//128p 500g -> 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<time.h>

#define popsize 128 //size of population 
#define note_size 7
#define MAXgeneration 500
#define TEMPO 600000

//declare structure
typedef struct note_set
{
		int note;
		struct note_set *next;
}note_set;

typedef struct node
{
		int attr;
		struct node *next;
		note_set *ptr;
}node;

typedef struct individual
{
		int fitness;
		node *next;
}individual;
typedef struct accomp_node
{
	int accomp_attr;
	int volume;
	int instrument;
}accomp_node;

typedef struct accomp_type
{
	accomp_node anode[8];
}accomp_type;

//global variable
accomp_type habanera[3];
int aaa=0;
int index_ch[2]={0},u_index,denominator=0,numerator=0;
int channel,MFile[3]={0},chord, KeySig =0,Ismajor=1;
int debug=0;

//LinkedList function------------------------------------------------
struct node *create_node(int attr)
{
	struct node *new_node;
	new_node = malloc(sizeof(struct node));
	new_node->attr = attr;
	new_node->ptr = NULL;
	new_node->next = NULL;
	return new_node;
}
struct note_set *create_note(int note)
{
	//printf("note...%d\n",note);
	struct note_set *new_note;
	new_note = malloc(sizeof(struct note_set));
	new_note->note = note;
	new_note->next = NULL;
	return new_note;
}
void assign(struct individual *a,struct individual *b) //複製LinkedList b 至 LinkedList a
{
	struct node *input_nd=NULL,*new_nd=NULL,*cur_nd=NULL;
	struct note_set *input_nt=NULL,*new_nt=NULL,*cur_nt=NULL;
	
	(*a).fitness = (*b).fitness;
	
	input_nd = (*b).next;
	while(input_nd != NULL)
	{
		new_nd = create_node(input_nd->attr);
		if((*a).next == NULL) (*a).next = new_nd;
		else cur_nd->next = new_nd;
		cur_nd = new_nd;
		
		input_nt = input_nd->ptr;
		while(input_nt != NULL)
		{
			new_nt = create_note(input_nt->note);
			if(cur_nd->ptr == NULL) cur_nd->ptr = new_nt;
			else cur_nt->next = new_nt;
			cur_nt = new_nt;
			input_nt = input_nt->next;
		}
		input_nd = input_nd->next;
	}
	//free memory...
	return;
}
//Accompaniment function---------------------------------------------
int Find_Max(int a, int b, int c)
{
		//printf("Compare: %d, %d, %d\n",a,b,c);
		int max = a;
		if(b > a)
			if(c > b)
				return 2;
			else
				return 1;
		if(c > a)
			if(b > c)
				return 1;
			else
				return 2;
		
		return 0;
}
int ha(struct node *check, int haba[][8], int score[])
{
		int count = 0, match_p = 0, match[3]={8,10,6}, MAX;
		int i;
		struct node *c=NULL;
		/*if(haba_n == 0)
			match = 8;
		else if(haba_n == 1)
			match = 10;
		else if(haba_n == 2)
			match = 6;*/
	//	printf("檢查第%d型態\n",haba_n+1);
		/*if(aaa > 0)
		{
			printf("%d : ",aaa);
			c=check;
			for(i=0;i<16;i++)
			{
				if(c == NULL) break;
				else {
					printf("%d ",c->attr);
					c = c->next;
				}
			}
			
			aaa++;
		}*/
		for(i=0;i<3;i++)
		{
			c = check;
		//while(c != NULL)
		//{
		//	count = 0;
		//	match_p = 0;
			while(1)
			{
				if(c == NULL) break;
				++count;
				if(haba[i][count%8] == 0 && c->attr == 0){
					score[i] += 2;			   //對齊成功(+2) 
					if(count%4 == 0) score[i]+=10; //accent
					++match_p;		
				}
				if(count%8==0 && count!=0){
					if(match_p == match[i] / 2)
						score[i] += 10;		   //一小節全對齊(+10)
				}
				if(count==16 && match_p==match[i]){
					score[i] += 30;		       //兩小節全對齊(+30)
					c = c->next;
					break;
				}
				c = c->next;
			}
		//}
		}
		//printf("\n");
		MAX = Find_Max(score[0],score[1],score[2]);
		//if(aaa>0) printf("||%d %d %d -> %d\n",score[0],score[1],score[2],MAX);
		return MAX;
}
//---------------------------------------------------------------------------
void initialAccompaniment()
{
	int i,j;
	int instrument=38; //打擊樂器 38小鼓1
	int accents_instrument=35; //重音所使用的打擊樂器 35大鼓1
	int volume = 50;
	int accents_volume = 75;
	int habaneranote[3][8]={ {0,-2,-2,0,0,-2,0,-2},
						   	{0,0,-2,0,0,-2,0,-2},
							{0,-1,-1,0,-1,-1,0,-1}};//habaneranote的節奏有三種
	for(i=0;i<3;i++)
	{
		for(j=0;j<8;j++)
		{
			habanera[i].anode[j].accomp_attr=habaneranote[i][j];
			habanera[i].anode[j].instrument = instrument;
			habanera[i].anode[j].volume = volume; //打擊的音量
			if(j%4==0) //重音的位置(1、3拍)
			{
				habanera[i].anode[j].volume = accents_volume; //更改重音音量
				habanera[i].anode[j].instrument = accents_instrument; //更改重音樂器
			}
		}
		
	}		
	for(i=0;i<3;i++)
	{
		for(j=0;j<8;j++)
		{
			printf("%d %d %d//",habanera[i].anode[j].accomp_attr,habanera[i].anode[j].instrument,habanera[i].anode[j].volume);
		}
		printf("\n");
	}	
}

accomp_node * createAccompaniment(struct node *cur,int count) //tango
{
	int i,j,times;
	int habaneranote[3][8]={ {0,-2,-2,0,0,-2,0,-2},
					   	{0,0,-2,0,0,-2,0,-2},
						{0,-1,-1,0,-1,-1,0,-1}};//habaneranote的節奏有三種
	int chosetype,nouse[3]={0};
	accomp_node *accomhead,*accom;//用成一條的比較好寫
	accom = malloc(sizeof(accomp_node));
	accomhead = accom;
	times = count/8+1; //兩小節一種所以除以8不是除以4
	printf("count: %d\n",count);
	
	for(i=0;i<times;i++)
	{
		for(j=0;j<3;j++) nouse[j] = 0;
		chosetype = ha(cur,habaneranote,nouse);
		printf("type: %d\n",chosetype);
		for(j=0;j<16;j++)
		{
			cur = cur->next;
			if(cur == NULL) j=16;
		}
		//chosetype = rand()%3; //tango的伴奏有三種，solea要再查，暫時寫死
		for(j=0;j<16;j++)//兩小節一種，所以兩個
		{
			*accom = habanera[chosetype].anode[j%8];
			accom++;
		}
		//for(j=0;j<8;j++)//兩小節一種，所以兩個
		//{
		//	*accom = habanera[chosetype].anode[j];
		//	accom++;
		//}
		if(cur == NULL) break;
	}
	accom = accomhead;
	return accomhead;
}
//---------------------------------------------------------------------------
void printindividual(individual x, individual y, char useless[][30], char filename[])
{
	if(debug) printf("---In printIndividual---\n");
	char name[25];
	/*strcpy(name,"o_");
	strcat(name,filename);
	strcat(name,".txt");*/
	FILE *fp = fopen("evo.txt","w");
	if(!fp) printf("Fail to open output file\n");
	
	int i,j, time_flag = 0, tempo_flag = 0, beat, time, index,ch,count=0;
	struct node *arrow=NULL,*last=NULL;
	struct note_set *tmp=NULL;
	int accomp_count=0, accomp_count_tmp=0, ancount; //printindividual裡兩個聲部的while迴圈中加count取node總數,取兩者中大的
	accomp_node *accom,*lastaccom, *arr;
	
	
	if(index_ch[1] == 0) MFile[1] = 3; //the number of (MTrk,TrkEnd)set
	else MFile[1] = 4;
	//beat = MFile[2];
	
	if(denominator == 0) denominator=4;
//	if(numerator == 2)
		//beat = beat*4 / denominator /2;
		beat = 120;
	//else beat = beat*4 / denominator; // 換成該拍號的基本音長度(beat為4分音符的長度) p.s.實際上要看將一個note設為多長 --> 之後改成自訂拍號(依各flamenco meter)
	
	
	fprintf(fp,"MFile %d %d %d\nMTrk\n",1,MFile[1],beat); //自訂beat
	fprintf(fp,"0 tempo %d\n",TEMPO);
	
	for(i=0; i<u_index; i++){
		
		//Write Useless
		if(strstr(useless[i],"TimeSig") != NULL){
			if(time_flag == 0){
				fprintf(fp,"%s",useless[i]);
				++time_flag;
			}	
		}
		/*else if(strstr(useless[i],"Tempo") != NULL || strstr(useless[i],"tempo") != NULL){
			if(tempo_flag == 0){
				fprintf(fp,"%s",useless[i]);
				++tempo_flag;
			}	
		}
		/*else if(strstr(useless[i],"MFile") != NULL){
			fprintf(fp,"%s",useless[i]);
			fprintf(fp,"MTrk\n");
		}*/
		else if(strstr(useless[i],"PrCh") != NULL)
			continue;
		else
			fprintf(fp,"%s",useless[i]);
	}
	
	
	//calculate total length of 2 individuals
	arrow = x.next; 
	while(arrow != NULL)
	{
		accomp_count++;
		arrow = arrow->next;
	}
	arrow = y.next;
	while(arrow != NULL)
	{
		accomp_count_tmp++;
		arrow = arrow->next;
	}
	
	if(accomp_count>=accomp_count_tmp) ancount=accomp_count;
	else 
	{
		ancount=accomp_count_tmp;
		printf("Accompaniment is longer~~\n");
	}
	fprintf(fp,"%d Meta TrkEnd\nTrkEnd\n",ancount*beat/4); 
	
	
	//Channel 1
	time=0; ch=1;
	arrow = x.next;
	last = arrow;
	
	fprintf(fp,"MTrk\n");
	for(i = 0 ; i < u_index ; i++)
		if(strstr(useless[i],"PrCh") != NULL)
			if(strstr(useless[i],"ch=1") != NULL)
				fprintf(fp,"%s",useless[i]);
		
	if(last->attr != -1) //第一個音為休止符 (目前create population後不會有這種情況，之後可以加)
	{
		tmp = arrow->ptr;
		while(tmp != NULL)
		{
			fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,tmp->note,100);
			tmp = tmp->next;
		}
	}
	while(arrow != NULL)
	{
		if(arrow->attr == -1) //目前node為休止符
		{
			if(last != NULL) //前面有音的話要關
			{
				tmp = last->ptr;
				while(tmp != NULL)
				{
					fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,tmp->note,0);
					tmp = tmp->next;
				}
				last = NULL;
			}
		}
		else if(arrow->attr == 0) //目前node有音
		{
				if(last == NULL) 
				{
					tmp = arrow->ptr;
					while(tmp != NULL)
					{
						fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,tmp->note,100);
						tmp = tmp->next;
					}
				}
				else{ //前面有音的話要關
					tmp = last->ptr;
					while(tmp != NULL)
					{
						fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,tmp->note,0);
						tmp = tmp->next;
					}
					tmp = arrow->ptr;
					while(tmp != NULL)
					{
						fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,tmp->note,100);
						tmp = tmp->next;
					}
					last = NULL;
				}
				last = arrow;
		}
		time += beat/4;
		arrow = arrow->next;
	}
	fprintf(fp,"%d Meta TrkEnd\nTrkEnd\n",time);
	
	//Channel 2(major Accompaniment)
	if(index_ch[1] != 0)
	{
		//Write Note ch2 (similar to ch1)
		time=0; ch=2; index=index_ch[1];
		arrow = y.next;
		last = arrow;
		
		fprintf(fp,"MTrk\n");
		for(i=0; i<index; i++)
			if(strstr(useless[i],"PrCh") != NULL)
				if(strstr(useless[i],"ch=2"))
					fprintf(fp,"%s",useless[i]);
			
		if(last->attr != -1)
		{
			tmp = arrow->ptr;
			while(tmp != NULL)
			{
				fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,tmp->note,100);
				tmp = tmp->next;
			}
		}
		while(arrow != NULL)
		{
			if(arrow->attr == -1)
			{
				if(last != NULL)
				{
					tmp = last->ptr;
					while(tmp != NULL)
					{
						fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,tmp->note,0);
						tmp = tmp->next;
					}
					last = NULL;
				}
			}
			else if(arrow->attr == 0)
			{
					if(last == NULL) 
					{
						tmp = arrow->ptr;
						while(tmp != NULL)
						{
							fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,tmp->note,100);
							tmp = tmp->next;
						}
					}
					else{
						tmp = last->ptr;
						while(tmp != NULL)
						{
							fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,tmp->note,0);
							tmp = tmp->next;
						}
						tmp = arrow->ptr;
						while(tmp != NULL)
						{
							fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,tmp->note,100);
							tmp = tmp->next;
						}
						last = NULL;
					}
					last = arrow;
			}
			time += beat/4;
			arrow = arrow->next;
		}
		fprintf(fp,"%d Meta TrkEnd\nTrkEnd\n",time);
	}
	//===================打擊伴奏==============	
	time=0; ch=10;
	arrow = x.next;
	accom = createAccompaniment(arrow, ancount);
	/*arr = accom;
	for(i=0;i<ancount;i++)
	{
		printf("%d ",arr->accomp_attr);
		arr++;
	}*/
	lastaccom = accom;
	fprintf(fp,"MTrk\n");
	printf("ancount = %d\n",ancount);
	while(ancount!=0)
	{
		if(accom->accomp_attr == -1) //目前node為休止符
		{
			if(lastaccom->accomp_attr != -1) //前面有音的話要關
			{
				fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,lastaccom->instrument,0);
			}
		}
		else if(accom->accomp_attr == 0) //目前node有音
		{
				if(lastaccom->accomp_attr == -1) 
				{
						fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,accom->instrument,accom->volume);
				}
				else{ //前面有音的話要關

						fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,lastaccom->instrument,0);
						fprintf(fp, "%d on ch=%d n=%d v=%d\n", time,ch,accom->instrument,accom->volume);
				}
		}
		time += beat/4;
		lastaccom = accom;
		accom++;
		ancount--;
	}
	fprintf(fp,"%d Meta TrkEnd\nTrkEnd\n",time);
	fclose(fp);
}
//-----------------------------------------------------------------------------------
void CreatePopulation(individual newpop[],individual ch[])
{
		struct node *input_nd=NULL,*new_nd=NULL,*cur_nd=NULL,*arrow=NULL;
		struct note_set *input_nt=NULL,*new_nt=NULL,*cur_nt=NULL,*tmp=NULL;
		int i,note;
		if(debug) printf("---Create Population---\n");
		for(i=0;i<popsize;i++)
		{
			
				if(channel == 1) input_nd = ch[0].next; //choose input
				else if(channel == 2) input_nd = ch[1].next;
				
				
				while(input_nd != NULL)
				{
						//之後可加休止符，讓曲子變成弱起拍(Upbeat) e.g. Solea
						//音
						new_nd = create_node(0);
						if(newpop[i].next == NULL)	newpop[i].next = new_nd;
						else cur_nd->next = new_nd;
						input_nt = input_nd->ptr;
						cur_nd = new_nd;
						
						do{
							new_nt = create_note(input_nt->note);
							if(new_nd->ptr == NULL)	new_nd->ptr = new_nt;
							else cur_nt->next = new_nt;
							cur_nt = new_nt;
							input_nt = input_nt->next;
						} while(input_nt != NULL);
						//加延長音-2
						if(channel == 2){
							while(rand()%2 == 0) //待修正(3/15/20為機率的大小可自訂)
							{
								new_nd = create_node(-2);
								new_nd->next = NULL;
								new_nd->ptr = NULL;
								cur_nd->next = new_nd;
								cur_nd = cur_nd->next;
							}
							if(rand()%15 == 0) //加休止符-1
							{
								new_nd = create_node(-1);
								new_nd->next = NULL;
								new_nd->ptr = NULL;
								cur_nd->next = new_nd;
								cur_nd =cur_nd->next;
								while(rand()%20 == 0) //加(休止符的)延長音-2
								{
										new_nd = create_node(-2);
										new_nd->next = NULL;
										new_nd->ptr = NULL;
										cur_nd->next = new_nd;
										cur_nd = cur_nd->next;
								}
							}
						}
						else{
							while(rand()%4 == 0) //待修正(3/15/20為機率的大小可自訂)
							{
								new_nd = create_node(-2);
								new_nd->next = NULL;
								new_nd->ptr = NULL;
								cur_nd->next = new_nd;
								cur_nd = cur_nd->next;
							}
							if(rand()%15 == 0) //加休止符-1
							{
								new_nd = create_node(-1);
								new_nd->next = NULL;
								new_nd->ptr = NULL;
								cur_nd->next = new_nd;
								cur_nd =cur_nd->next;
								while(rand()%20 == 0) //加(休止符的)延長音-2
								{
										new_nd = create_node(-2);
										new_nd->next = NULL;
										new_nd->ptr = NULL;
										cur_nd->next = new_nd;
										cur_nd = cur_nd->next;
								}
							}
						}
						
						input_nd = input_nd->next;
				}
		}
		return;

}
//-----------------------------------------------------------------------------------
//fitness rule  
void fitnessfunction(individual p[],int size)
{
		struct node *cur=NULL;
		
		int count = 0, score = 0,ha_score[3]={0}, choose;
		int i,j,length = 0;
		int habaneranote[3][8]={ {0,-2,-2,0,0,-2,0,-2},
						   	{0,0,-2,0,0,-2,0,-2},
							{0,-1,-1,0,-1,-1,0,-1}};//habaneranote的節奏有三種
		for(i=0;i<size;i++)
		{
			//Rule with Habanera
			cur = p[i].next;
			while(cur != NULL)
			{
				//printf("i= %d\n",i);
				for(j=0;j<3;j++) ha_score[j]=0;
				//Rule2.3
				choose = ha(cur,habaneranote,ha_score);
	//			printf("%d\n",ha_score[choose]);
				score += ha_score[choose];
				++length;
				for(j=0;j<16;j++)
				{
				//printf("j= %d\n",j);
					cur = cur->next;
					if(cur == NULL) break;
				}
			}
			//printf("after cur\n");
			score = (int)(score / length); //標準化 habarnera 部分的分數，以解決個體長度不一的問題
			//printf("i= %d\n",score);
			cur = p[i].next;
			while(cur != NULL)
			{
				//Rule1: 音符長度
				if(cur->attr == 0 || cur->attr == -1) count = 0;
				else {
					++count;
					//重複扣分? 10個要比8個扣更多? 分數? 休止符和音的長度規範要不一樣?
					if(count > 4){   //標準：基本音X+1倍
						score -= 10; //目前：每多一個扣X分(重複扣分)
					} 
				}
				cur = cur -> next;
			}
			//printf("score = %d\n",score);
			//printf("length = %d\n",length);
			p[i].fitness = score;
			score = 0;
			length = 0;
		}
		return;
}
//accompaniment fitness function---------------------------------------------
void acc_fitnessfunction(individual p[],struct node *melody, int size)
{
	struct node *cur=NULL, *mcur=NULL;
	struct note_set *cur_note=NULL, *mcur_nt=NULL, *cur_node=NULL, *chord_sequence=NULL;
	int i,j,score=0,note;
	int length=0,length2=0,total,flag=0,count, max=0,maxi,l,f;
	int chord_set[7][4] = {{0,3,7,10},{1,5,8,0},{3,7,10,1},{0,3,5,8},{7,10,1,5},{8,0,3,7},{10,1,5,8}}, match[7]={1,1,1,1,-1,0,0};
	if(debug) printf("---In acc_accompaniment\n");
	aaa++;
	/*if(aaa == 2)
	{
		cur = melody;
		while(cur != NULL)
		{
			printf("%d ",cur->attr);
			cur = cur->next;
		}
	//}*/
	mcur = melody;
	while(mcur != NULL) //取得主旋律長度、每小節的和弦
	{
		length++;
		mcur_nt = mcur->ptr;
		while(mcur_nt != NULL) //計算該小節中與各chord音match的數量
		{
			note = mcur_nt->note;
			for(i=0;i<7;i++) 
				for(j=0;j<4;j++)
					if((note+chord)%12 == (chord_set[i][j]+chord)%12) match[i]++;
				
			mcur_nt = mcur_nt->next;
		}
		if(length%8 == 0) //每一個小節決定一次
		{
			for(i=0;i<7;i++)
			{
				if(max < match[i])
				{
					max = match[i];
					maxi = i;
				}
				//Initialize array 給I II III IV多一點機會，V(diminished)少一點
				if(i<=3) match[i] = 1;
				else if(i==4) match[i] = -1;
				else match[i] = 0;
			}
			if(chord_sequence == NULL) //chord依順序存在chord_sequence 的LinkedList中
			{
				chord_sequence = create_note(maxi);
				cur_node = chord_sequence;
			}
			else 
			{
				cur_node->next = create_note(maxi);
				cur_node = cur_node->next;
			}
		}
		mcur = mcur->next;
	}
	cur_node->next = NULL;
	
	cur_node = chord_sequence;
	/*while(cur_node != NULL)
	{
		printf("%d ",cur_node->note);
		cur_node = cur_node->next;
	}*/
	
	for(i=0;i<size;i++) 
	{
		score = 0;
		flag = 0;
		cur = p[i].next;
		while(cur != NULL)
		{
			length2++;
			cur = cur->next;
		}
		//Rule1: 調整node長度
		if(length > length2) 
		{
			total = length;
			if(abs((length-length2))*5 > total) 
			{
				score -= 30; //差距大於總長度的 1/5
				flag = 1; //希望第二聲部node長一點
			}
		}
		else if(length < length2)
		{
			total = length2;
			if(abs((length-length2))*5 > total) 
			{
				score -= 30; //差距大於總長度的 1/5 -> 先扣一次
				flag = 2; //希望第二聲部node短一點
			}
		}
		else score += 150; //perfect length
		if(flag != 0)
		{
			cur = p[i].next;
			while(cur != NULL)
			{
				if(cur->attr == 0 || cur->attr == -1) count = 0;
				else {
					++count;
					//重複扣分? 10個要比8個扣更多? 分數? 休止符和音的長度規範要不一樣?
					if(count > 4){
						if(flag == 1) score += 5; //太長加分 ***Rule1***
						else if(flag == 2) score -= 5; //太長扣分 ***Rule2***
					} 
				}
				cur = cur -> next;
			}
		}
		
		l=1;
		cur = p[i].next;
		mcur = melody;
		cur_node = chord_sequence;
		maxi = cur_node->note; //該小節chord
		while(mcur != NULL && cur != NULL)
		{
			//主旋律為休止符或延長音時 伴奏有音 //該伴奏是否有chord note
			if(cur->attr == 0 && mcur->attr != 0) //***Rule3***
			{
				if(mcur->attr == -1) score += 10;
				else if(mcur->attr == -2) score += 20;
				
				cur_note = cur->ptr;
				while(cur_note != NULL) //比對:該音為chord note就加分
				{
					for(j=0;j<4;j++)
						if((cur_note->note+chord)%12 == (chord_set[maxi][j]+chord)%12) score += 30; //***Rule4***
					cur_note = cur_note->next;
				}
			}
			if(l%8 == 0 ) //每一小節從chord sequence中提出當前的chord
			{
				cur_node = cur_node->next;
				if(cur_node->next == NULL) break;
				maxi = cur_node->note; //該小節chord
			}
			mcur = mcur->next;
			cur = cur->next;
			l++;
		}
		p[i].fitness = score;
	}
	return;
}
//selection
void tournamentselection (individual p[],individual result[])
{
		int choose1,choose2,i,j;
		//fitnessfunction(p,popsize);
		for(i=0;i<2;i++)
		{
				choose1 = rand()%popsize;
				while(1){
						choose2 = rand()%popsize;
						if(choose2 != choose1) break;
				}
				if(p[choose1].fitness >= p[choose2].fitness) assign(&result[i],&p[choose1]);
				else assign(&result[i],&p[choose2]);
		}
		return;
}
//Reproduce
void twopointcrossover(individual parent[],individual child[])
{
		struct node *cur_x=NULL,*cur_y=NULL,*after_x=NULL,*after_y=NULL;
		int count_x=1,count_y=1,p1,p2,index,tmp;
		
		if(channel == 1) index = index_ch[0];
		else if(channel == 2) index = index_ch[1];
		
		p1 = rand() % index;
		while(1) {
				p2 = rand() % index;
				if(p2 != p1) break;
		}
		if(p1 > p2) {tmp=p1; p1=p2; p2=tmp;} //p1<p2
		
		child[0] = parent[0];
		child[1] = parent[1];
		cur_x = child[0].next;
		cur_y = child[1].next;
		//printf("p1:%d p2:%d\n",p1,p2);
		while(count_x < p1 || count_y < p1)
		{
			if(count_x < p1 && cur_x->next != NULL)
			{
				cur_x = cur_x->next;
				if(cur_x->attr == 0) count_x++;
			}
			if(count_y < p1 && cur_y->next != NULL)
			{
				cur_y = cur_y->next;
				if(cur_y->attr == 0) count_y++;
			}
		}
		after_x = cur_x->next; after_y = cur_y->next;
		cur_x->next = after_y; cur_y->next = after_x;
		
		while(count_x < p2 || count_y< p2)
		{
			if(count_x < p2 && cur_x->next != NULL)
			{
				cur_x = cur_x->next;
				if(cur_x->attr == 0) count_x++;
			}
			if(count_y < p2 && cur_y->next != NULL)
			{
				cur_y = cur_y->next;
				if(cur_y->attr == 0) count_y++;
			}
		}
		after_x = cur_x->next; after_y = cur_y->next;
		cur_x->next = after_y; cur_y->next = after_x;
		
		child[0].fitness = -99999; 
		child[1].fitness = -99999; 
		return;
}
//mutate
void mutate(individual child[])
{
		struct node *cur=NULL,*tmp=NULL,*delete=NULL,*new_nd=NULL;
		int index;
		int choose;
		int k=0,i,j;
		int flag=0;
		
		for(i=0;i<2;i++)
		{
			if(channel==1) index = index_ch[0];
			else if(channel==2) index = index_ch[1];
			cur = child[i].next;
			while(cur != NULL)
			{
				if(cur->attr == 0 && rand()%index == 0){
					tmp = cur->next;
					while(tmp != NULL)
					{
						if(tmp->attr == 0) break;
						else {
							delete = tmp;
							tmp = tmp->next;
							free(delete);
						}
					}
					
					while(rand()%10 == 0) //待修正(3/15/20為機率的大小可自訂)
					{
							new_nd = create_node(-2);
							cur->next = new_nd;
							cur = cur->next;
					}
					if(rand()%15 == 0)
					{
							new_nd = create_node(-1);
							cur->next = new_nd;
							cur = cur->next;
							while(rand()%20 == 0) 
							{
									new_nd = create_node(-2);
									cur->next = new_nd;
									cur = cur->next;
							}
					}
					cur->next = tmp;
				}
				cur = cur->next;
			}
		}
		delete = NULL;
		return;
}
//survivor
int quick_sort(individual *np,int low,int high) {  
   int pivot_point,pivot_item,i,j;
   individual temp;  
   // 指標交界結束排序  
   if(high<=low){return 1;}  
   // 紀錄樞紐值  
   pivot_item = np[low].fitness;  
   j=low;  
     
   // 尋找比樞紐小的數  
   for(i=low+1; i<=high; i++) {  
       // 跳過等於或大於的數  
       if(np[i].fitness<=pivot_item){continue;}  
       j++;  
       // 交換 array[i] , array[j]  
       temp = np[i];  
       np[i] = np[j];  
       np[j] = temp;  
   }  
  
   // 將樞紐位址移到中間  
   pivot_point=j;  
   // 交換 array[low] , array[pivot_point]  
   temp = np[low];  
   np[low] = np[pivot_point];  
   np[pivot_point] = temp;  
  
   // 遞迴處理左側區段  
   quick_sort(np,low,pivot_point-1);  
   // 遞迴處理右側區段  
   quick_sort(np,pivot_point+1,high);  
   return 1;  
}
void survivor(individual newp[],individual p[]) // new poplulation (1*popsize) <-- parents & child (totally 3*popsize)
{
	struct node *cur_nd=NULL,*delete_nd=NULL;
	struct note_set *cur_nt=NULL,*delete_nt=NULL;
	int i;
	
	quick_sort(p,0,3*popsize-1);
	//for(i=0;i<3*popsize;i++){printf("%d- ",p[i].fitness);}
	//printf("\n");
	
	for(i=0;i<popsize;i++){ newp[i] = p[i];}
	for(i=popsize;i<3*popsize;i++) //free memory
	{
		cur_nd = p[i].next;
		while(cur_nd != NULL)
		{
			cur_nt = cur_nd->ptr;
			while(cur_nt != NULL)
			{
				delete_nt = cur_nt;
				cur_nt = cur_nt->next;
				free(delete_nt);
				
			}
			delete_nd = cur_nd;
			cur_nd = cur_nd->next;
			free(delete_nd);
		}
	}
	delete_nt = NULL;
	delete_nd = NULL;
	
	return;
}
//best result is not required because the newpop has been already sorted.

//  GA  
void GA(individual p[],struct node *x)
{
		individual newpop[popsize*3];
		individual child[2],parent[2];
		struct node *arrow=NULL;
		struct note_set *tmp=NULL;
		int i,j,g;
		if(debug) printf("in GA\n");
		
		for(g=1;g<=MAXgeneration;g++)
		{
				if(debug) printf("### Generation: %d ###\n",g);
				//Initialize the new population
				for(i=0;i<3*popsize;i++){
						newpop[i].fitness = -99999; //for evaluation
						newpop[i].next = NULL;
				}
				for(i=0;i<2;i++)
				{
					parent[i].next = NULL;
					child[i].next = NULL;
				}
				
				
				//start GA
				if(debug) printf("start GA\n\n");
				for(i=0;i<popsize;i++)
				{
						//selection
						if(debug) printf("---selection:%d---\n",i);
						tournamentselection(p,parent);
						
						
						//reproduction 
						if(debug) printf("---crossover:%d---\n",i);
						twopointcrossover(parent,child);
						
						//mutate
						if(debug) printf("---mutation:%d---\n",i);
						mutate(child);
						
						//add to new population
						newpop[i] = child[0];
						newpop[i + popsize] = child[1];
						
						for(j=0;j<2;j++)
						{
							parent[j].next = NULL;
							child[j].next = NULL;
						}		
				}
				//evaluation
				if(channel == 1) fitnessfunction(newpop,2*popsize);
				else if(channel == 2) acc_fitnessfunction(newpop,x,2*popsize);
				
				//survival
				for(i=2*popsize;i<3*popsize;i++) 
				{
					newpop[i] = p[i-2*popsize]; //copy parents into newpop
					p[i-2*popsize].fitness = -99999;
					p[i-2*popsize].next = NULL;
				}
				if(debug) printf("\nsurvival\n\n");
				survivor(p,newpop);
		}
		if(debug) printf("\n\n");
		return;
}

void Modulation(individual ch[]) //轉調 // -6 -5 -4 -3 -2 -1 0  1  2  3  4  5  6
{                                       // G- D- A- E- B- F- C G+ D+ A+ E+ B+ F+
	struct node *cur_node = NULL;
	struct note_set * cur_note = NULL;
	int i,j,x,last_nt1,last_nt2=0;
	if(Ismajor == 1)
	{
		switch(KeySig)
		{
			case  1: chord =  7; printf("Gmajor-->Bphygian\n");break;
			case  3: chord =  9; break;
			case  5: chord = 11; break;
			case  6: chord =  6; break;                           
			case -1: chord =  5; break;
			case -2: chord = 10; break;
			case -3: chord =  3; break;
			case -4: chord =  8; break;
			case -5: chord =  1; break;
			case -6: chord =  6; break;
			default: break;
		}
	}
	else if(Ismajor == 0)
	{
		switch(KeySig)
		{
			case  0: chord = 9; break;
			case  1: chord = 4; break;
			case  2: chord =11; break;
			case  3: chord = 6; break;
			case  4: chord = 1; break;
			case  5: chord = 8; break;
			case  6: chord = 3; break;                           
			case -1: chord = 2; break;
			case -2: chord = 7; break;
			case -3: chord = 0; break;
			case -4: chord = 5; break;
			case -5: chord =10; break;
			case -6: chord = 3; break;
			default: break;
		}
	}
	for(i=0;i<2;i++)
	{
		cur_node = ch[i].next;
		while(cur_node != NULL)
		{
			cur_note = cur_node->ptr;
			while(cur_note != NULL)
			{
				x = cur_note->note %12;
				last_nt1 = cur_note->note;
				// if (x == (chord+2)%12 || x == (chord+4)%12 ||x == (chord+9)%12 ||x == (chord+11)%12 ) cur_note->note -= 1; //Ionian(major) -> Phygian(平行轉調)
				if(Ismajor == 1)
				{
					/*if (x == (chord+2)%12 || x == (chord+4)%12 || x == (chord+9)%12 || x == (chord+11)%12 ) cur_note->note += 3;
					else cur_note->note += 4;*/
					if (x == (chord+2)%12 || x == (chord+4)%12 || x == (chord+9)%12 || x == (chord+10)%12 || x == (chord+11)%12) cur_note->note += 3; //Ionian(major) -> Phygian
					else if(x == (chord)%12 || x == (chord+5)%12 || x == (chord+6)%12 || x == (chord+7)%12) cur_note->note += 4;
					else if(x == (chord+1)%12 || x == (chord+8)%12) //避免半音變成同一個音
					{
						//if(last_nt2 == (cur_note->note+1)) cur_note->note += 3;
						//else 
							cur_note->note += 4;
					}
					else if(x == (chord+3)%12) //phygian dominant in ascend
					{
						//if(last_nt2 < cur_note->note) cur_note->note += 4;
						//else
						//cur_note->note += 3;
						cur_note->note += 4;
					}
				}
				else if(Ismajor == 0)
				{
					if (x == (chord+2)%12) cur_note->note -= 6;
					else cur_note->note -= 5;
				}
				cur_note = cur_note->next;
			}
			last_nt2 = last_nt1;
			cur_node = cur_node->next;
		}
	}
	return;
}

void input(struct individual ch[], char useless[][30], char filename[])
{
		int s_i, flag=0, i,j,index,base; //input_index, useless_index
		int time,ch_,note,vol;
		FILE *fp;
		char s[30];
		char *temp;
		char filename2[20];
		struct note_set *new_note=NULL,*current=NULL;
		struct node *tmp=NULL,*now_1=NULL,*now_2=NULL;
		
		
		strcpy(filename2,filename);
		fp = fopen(strcat(filename2,".txt"),"r");
		if (!fp) {
				strcpy(filename2,filename);
				fp = fopen(strcat(filename2,".TXT"),"r");
				if (!fp) {
						printf("檔案建立失敗...\n");
						exit(1);
				}
		} 
		//Initialization
		while (fgets(s, 30, fp) != NULL) {
				if(strstr(s,"On")!= 0 || strstr(s,"Off")!= 0 || strstr(s,"on")!= 0 || strstr(s,"off")!= 0){
						//convert to chromosome
						temp = strtok(s, " ");
						flag = 0;
						for(i=0;i<5;i++){ // 取得ch n的值，藉由判斷On,off 以及v 決定是否存該note
								if(temp == NULL) 
								{
										printf("stop on %d \n",i);
										continue;
								}
								switch (i) {
										case 0:
												time = atoi(temp);
												break;
										case 1:
												if(strcmp(temp,"On")==0 || strcmp(temp,"on")==0) flag=1;
												else 
												{
													i=5; //Ignore this line
													flag = 0;
												}
												break;
										case 2:	
												for(s_i = 0 ; s_i < strlen(temp) ; s_i++){
														if(temp[s_i] > '0' && temp[s_i] <= '9'){
																ch_ = (int)(temp[s_i]-'0');
														}
												}
												//printf("ch = %d ",ch);

												break;
										case 3:
												note = 0;
												base=10;
												for(s_i = 0 ; s_i < strlen(temp) ; s_i++){
														if(temp[s_i] >= '0' && temp[s_i] <= '9'){
																note += (int)(temp[s_i]-'0') * base;
																base /= 10;
														}
														
												}
												//printf("note = %d\n",note);
												break;
										case 4:
												if(strcmp(temp,"v=0")==0 || strcmp(temp,"v=0\n")==0 || strcmp(temp,"v=0\r\n")==0) 
												{
													flag=0;
													i=5;
												}
												else 
												{
													//for(j=0;j<strlen(temp);j++)
													//printf("%d ",temp[j]);
													//printf("\n");
												} 
												break;
								}
								temp = strtok(NULL, " ");
						}
						if(flag==1) {
								if(ch_ == 1) {
									if(now_1 == NULL || time != now_1->attr) // 開始時間不同
									{
										tmp = create_node(time);
										if(ch[0].next == NULL) ch[0].next = tmp;
										else now_1->next = tmp;
										now_1 = tmp;
									}
									new_note = create_note(note);
									
									if(now_1->ptr == NULL)	// 第一次將note放入node
										now_1->ptr = new_note;
									else // current:當前note
									{
										current = now_1->ptr;
										while(current->next != NULL)
											current = current->next;
										current->next = new_note;
									}						
								}
								else if(ch_ == 2) {
									if(now_2 == NULL || time != now_2->attr)
									{
										tmp = create_node(time);
										if(ch[1].next == NULL) ch[1].next = tmp;
										else now_2->next = tmp;
										now_2 = tmp;
									}
									new_note = create_note(note);
									if(now_2->ptr == NULL)
										now_2->ptr = new_note;
									else
									{
										current = now_2->ptr;
										while(current->next != NULL)
											current = current->next;
										current->next = new_note;
									}					
								}
						}
				}
				else if(strstr(s,"MFile")!=0){ //MFile 1 5 384
						temp = strtok(s, " ");
						for(i=0;i<3;i++){
								temp = strtok(NULL," ");
								MFile[i] = atoi(temp);
						}
				}
				else if(strstr(s,"KeySig")!=0){
						temp = strtok(s, " ");
						for(i=0;i<3;i++){
								temp = strtok(NULL," ");
								if(i == 1) KeySig = atoi(temp);                       // -6 -5 -4 -3 -2 -1 0  1  2  3  4  5  6
								if(i == 2 && strstr(temp,"minor")!=0) Ismajor = 0;    // G- D- A- E- B- F- C G+ D+ A+ E+ B+ F+
								//printf("%d ",KeySig); 
						}
				}
				else if(strstr(s,"TimeSig")!=0){
						strcpy(useless[u_index],s);
						u_index++;
						temp = strtok(s, " ");
						for(i=0;i<2;i++){
								temp = strtok(NULL," ");
						}
						numerator = temp[0] - '0'; //e.g. 6/8 : x=6 y=8
						denominator = temp[2] - '0';
				}
				else if(strstr(s,"Pb")!=0 || strstr(s,"PrCh")!=0){ //recyclable  ||(s[0]=='0' && strstr(s,"Tempo")!=0)
						strcpy(useless[u_index],s);
						u_index++;
				}
				else { //unrecyclable
						continue;
				}
		}
		//printf("beat=%d x=%d y=%d\n",beat, x, y);
		fclose(fp);
		return;
}
/*-------------------------------------------------------------------------------*/
void main(int argc, char* argv[])
{
		clock_t start_time, end_time;
		float total_time = 0;
		
		srand((unsigned)time(NULL));
		individual ch[2]; //input
		individual newpop[popsize],x,y; //GA
		node *arrow=NULL;
		note_set *tmp=NULL;
		int i,choose;
		char useless[10000][30];
		int *ptr;
		if(argc < 2) {
			printf("Please enter the filename\n");
			exit(1);
		}
		start_time = clock();
		for(i=0;i<2;i++) ch[i].next = NULL;
		input(ch, useless, argv[1]);
		Modulation(ch);
		if(debug) printf("chord = %d \n",chord);
		
		for(i=0;i<2;i++) //calculate length of individual
		{
			arrow = ch[i].next;
			while(arrow != NULL)
			{
				index_ch[i]++;
				arrow = arrow->next;
			}
		}
		if(debug) printf("[nodelength] ch1:%d ch2:%d\n",index_ch[0],index_ch[1]);
		/*//int a=0,b=0;
		arrow = ch[0].next; //test "input"
		while(arrow!=NULL)// && b<3)
		{	
			tmp = arrow->ptr;
			while(tmp!=NULL)
			{
				printf("1: %d ",tmp->note);
				tmp=tmp->next;
			}
			printf(" || ");
			arrow = arrow->next;
			//b++;
		}
		
		arrow = ch[1].next;
		while(arrow!=NULL && a<3)
		{	
			tmp = arrow->ptr;
			printf("2: ");
			while(tmp!=NULL)
			{
				printf("%d ",tmp->note);
				tmp=tmp->next;
			}
			printf("\n");
			arrow = arrow->next;
			a++;
		}*/

		
		//printf("index: %d %d \n",ch1_index,ch2_index);
		
		//for(i=0;i<u_index;i++) printf("%s",useless[i]);
		channel = 1;
		for(i=0;i<popsize;i++) newpop[i].next = NULL;
		initialAccompaniment();
		CreatePopulation(newpop,ch);
		choose = rand()%popsize;
		fitnessfunction(newpop,popsize);
		
		/*for(i=0;i<popsize;i++) //test "Create population"
		{
			printf("pop%d:\n",i);
			arrow = newpop[i].next;
			while(arrow != NULL)
		
			{
				tmp = arrow->ptr;
				if(arrow->attr == 0){
					while(tmp != NULL)
					{
						printf("%d ",tmp->note);
						tmp = tmp->next;
					}
				}
				else printf("%d ",arrow->attr);
				printf(" , ");
				arrow = arrow->next;
			}
			printf("\n");
		}*/
		GA(newpop,x.next); //x here is useless
		x.fitness = newpop[0].fitness;
		x.next = newpop[0].next;
		
		
		if(index_ch[1] > 0) //channel 2 exists
		{
			for(i=0;i<popsize;i++)
			{
				newpop[i].fitness = -99999;
				newpop[i].next = NULL;
			}
			printf("Channel2\n\n");
			channel = 2;
			CreatePopulation(newpop,ch);
			acc_fitnessfunction(newpop,x.next,popsize);
			GA(newpop,x.next); // x is used for passing to acc_fitnessfunction in GA
			y.fitness = newpop[0].fitness;
			y.next = newpop[0].next;
		}
		if(debug) printf("----------------------------------------\n");
		//CA = chord_accompaniment();
		printindividual(x,y,useless,argv[1]);
		printf("Complete~~\n");
		
		end_time = clock();
		total_time = (float)(end_time-start_time)/CLOCKS_PER_SEC;
		printf("Time : %f sec \n", total_time);
		
		/*for(i=0; i<popsize; i++) free(newpop[i]);
		for(i=0; i<2; i++) free(ch[i]);
		free(x);
		free(y);*/
		return;
}


