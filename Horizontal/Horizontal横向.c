#include <stdio.h>

int main()
{
	//### 可调整变量 - 控制程序效果
	double Data[500] = {0}; //存储输入数据
	double MaxLong = 35; //条柱长度限制


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
		if(Data[i] < 0 || i >= 500) break; //结束判断
		if(Data[i] == 0) i--; //忽略0值
	}


	//### 补充数据 - 填充公式与寻找极端数据
	//公式: 条柱长度 = 数据 * (条柱长度限制 / 最大数据)
	double MinData = Data[0];
	double MaxData = 0;

	//寻找极端数据
	for(int i = 0;;i++)
	{
		if(Data[i] < 0) break; //结束判断
		if(Data[i] < MinData) MinData = Data[i]; //赋值为"更小值"
		if(Data[i] > MaxData) MaxData = Data[i]; //赋值为"更大值"
	}


	//### 绘制条柱
	printf("\e[1J\e[H\n\n"); //清空屏幕

	for(int i = 0;;i++)
	{
		if(Data[i] < 0) break; //结束判断

		//设置文本颜色 - 标记极端数值
		if(Data[i] == MaxData) printf("\e[32m"); //最大:绿色
		if(Data[i] == MinData) printf("\e[31m"); //最小:红色

		//绘制条柱
		if(Data[i] * (MaxLong / MaxData) < 1) printf(":"); //防止出现空条柱

		for(int l = Data[i] * (MaxLong / MaxData);l > 0;l--)
			printf("="); //这是条柱

		printf("   %.3lf\n", Data[i]); //标记具体数值
		printf("\e[0m"); //初始化文本
	}
	
	//### 等待用户观察 - 防止自动退出
	printf("\n\n\nPress Enter to end the program.\n");
	printf("按下回车键结束程序.\n");
	getchar();

	return 0;
}