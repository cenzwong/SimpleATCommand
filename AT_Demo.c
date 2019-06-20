//to be continue
//========or in Pure C Code===============
//========eg: in atmel device (SAMD21)===========
bool ATReturnCheck_C(
  uint8_t** toDEBUG,
  uint8_t** toATCommand,
  uint8_t* checkMessgae,
  bool isForcePass,
  bool isPrintATReturn,
  uint8_t* returnAT)
{
  do
  {
    UART_DBG_Print(toDEBUG);
    UART_SIN_Print(toATCommand);
    while(!SIM_TXC_Flag);
    my_delay_ms(100);
    if(SIM_RXC_Flag){
      SIM_RXC_Flag = false;
      int len = io_read(IO_SIM, returnAT, 1024);
      returnAT[len] = 0;
      if(isPrintATReturn){
        UART_DBG_Print("<<");
        UART_DBG_Print(returnAT);
      }
      if(strcmp(returnAT, checkMessage) == 0){return true}
    }

    my_delay_ms(1000);
  } while (isForcePass);

  return false;
  }

  //===> other function

//UART==
void UART_Setup(){
    usart_async_register_callback(&UART_DBG,USART_ASYNC_TXC_CB,tx_cb_UART_DBG);
    usart_async_register_callback(&UART_DBG,USART_ASYNC_RXC_CB,rx_cb_UART_DBG);

}

//TIMER==
  void SysTick_Handler(void){
    msTick++;
  }

  void my_delay_ms(uint32_t u32Ms){
    uint64_t current_time = msTick;
    while(msTick - current_time < u32Ms);
  }
