# LierdaEC_NB81&MB26_OpenCPU_DemoCode
 Lierda NB81 and MB26 modules OpenCPU DemoCode

Demo 程序主要以测试 AT 指令、 ADC、 GPIO（加中断） 、 I2C、 SPI、 PWM、 定时器、
串口、下行数据处理以及队列消息发送与接收为目的， Demo 程序创建了五个任务，
lierdaEC_APP_Task 任务用于跑测试函数（ADC、 AT 指令、 Timer、 PWM、 SPI、 串口、两个
log 打印函数，如图 1-1） ； lierdaEC_USART_Task 任务用于处理串口接收数据（如图 1-2） ；
lierdaEC_UPdata_Task 任务用于处理上行发送数据（如图 1-3） ； lierdaEC_Downdata_Task 任
务用于下行数据接收（如图 1-4） ； lierdaEC_TCPIP_Task 用于处理 UDP/TCP。