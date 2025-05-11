#include <stdio.h>

int main()
{
	//### 可调整变量 - 控制程序效果
	double Data[500] = {0}; //存储输入数据
	int BarLong[500] = {0}; //存储条柱长度
	int MaxLong = 12; //条柱长度限制
	
	
	//### 引导提示
	printf("Please enter the data (up to 500 items, enter a negative number to end):\n");
	printf("请输入数据(最多500项,输入负数结束):\n");


	//### 存储输入数据
	for(int i = 0;;i++)
	{
		//判断输入内容
		if(scanf("%lf", &Data[i]) != 1)  
		{
			//错误警告
			printf("\e[31;1mDO NOT ENTER NON-NUMBER CONTENT!\n");
			printf("请勿输入非数字内容!\e[0m\n");
		}

		//清除输入缓存区 - 避免扰乱数据和影响判断
		while(getchar() != '\n'); 

		//异常判断
		if(Data[i] < 0 || i >= 500) break; //结束检测
		if(Data[i] == 0) i--; //忽略0值
	}


	//### 处理数据 - 填充公式与寻找极端数据
	//公式: 条柱长度 = 数据 * (条柱长度限制 / 最大数据)
	int MinData = 0;
	int MaxData = 0;

	//寻找极端数据
	for(int i = 0;Data[i] > 0;i++)
	{
		if(Data[i] <= Data[MinData]) MinData = i; //赋值为"更小项"
		if(Data[i] >= Data[MaxData]) MaxData = i; //赋值为"更大项"
	}

	printf("\e[1J\e[H\n\n"); //清空屏幕

	//输出数据与存储条柱长度
	for(int i = 0;Data[i] > 0;i++)
	{
		BarLong[i] = Data[i] * (MaxLong / Data[MaxData]); //存储条柱长度
		if(BarLong[i] <= 0) BarLong[i] = 1; //防止出现空条柱
		
		//设置文本颜色 - 标记极端数值
		if(i == MaxData) printf("\e[32m"); //最大:绿色
		if(i == MinData) printf("\e[31m"); //最小:红色
		printf("%.1lf ", Data[i]); //提前输出原数据
		printf("\e[0m"); //初始化文本
	}
	printf("\n\n"); //换行

	//计算各项数据所占字符
	for(int i = 0;Data[i] > 0;i++)
	{
		int c = 0; //临时存储字符数
		while((int)Data[i] > 0)
		{
			Data[i] /= 10;
			c++;
		}
		Data[i] = c + 1; //"+1"是为了保持间距
	}


	//### 绘制条柱
	for(int i = 0;;i++)
	{
		//换行并重新检测
		if(Data[i] < 0)
		{
			printf("\n");
			i = 0;
			MaxLong--;
			if(MaxLong == 0) break; //结束检测
		}

		int KeepSpace = Data[i]; //复制
		//检测每行符合高度的条柱
		if(BarLong[i] == MaxLong)
		{
			//设置文本颜色 - 标记极端数值
			printf("\e[0m"); //初始化文本
			if(i == MaxData) printf("\e[32m"); //最大:绿色
			if(i == MinData) printf("\e[31m"); //最小:红色

			printf("||"); //这是条柱
			//保持间距
			while(KeepSpace > 0)
			{
				printf(" ");
				KeepSpace--;
			}
			BarLong[i]--;
		}
		else
		{
			printf("  "); //条柱符号为2个字符
			//空格占位
			while(KeepSpace > 0)
			{
				printf(" ");
				KeepSpace--;
			}
		}
	}


	//### 等待用户观察 - 防止自动退出
	printf("\n\n\nPress Enter to end the program.\n");
	printf("按下回车键结束程序.\n");
	getchar();

	return 0;
}