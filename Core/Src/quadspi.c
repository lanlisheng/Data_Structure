/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.c
  * @brief   This file provides code for the configuration
  *          of the QUADSPI instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "quadspi.h"

/* USER CODE BEGIN 0 */
static uint8_t QSPI_WriteEnable(void);
static uint8_t QSPI_AutoPollingMemReady(void);
static uint8_t QSPI_Configuration(void);
static uint8_t QSPI_ResetChip(void);
static uint8_t QSPI_QPIModeEnable(void);
volatile uint8_t QPI_Mode_Enabled_Flag;
/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 2;
  hqspi.Init.FifoThreshold = 4;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 24;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_4_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_3;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspInit 0 */

  /* USER CODE END QUADSPI_MspInit 0 */
    /* QUADSPI clock enable */
    __HAL_RCC_QSPI_CLK_ENABLE();

    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**QUADSPI GPIO Configuration
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF8     ------> QUADSPI_BK1_IO0
    PF9     ------> QUADSPI_BK1_IO1
    PB2     ------> QUADSPI_CLK
    PB6     ------> QUADSPI_BK1_NCS
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* QUADSPI interrupt Init */
    HAL_NVIC_SetPriority(QUADSPI_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(QUADSPI_IRQn);
  /* USER CODE BEGIN QUADSPI_MspInit 1 */

  /* USER CODE END QUADSPI_MspInit 1 */
  }
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspDeInit 0 */

  /* USER CODE END QUADSPI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_QSPI_CLK_DISABLE();

    /**QUADSPI GPIO Configuration
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF8     ------> QUADSPI_BK1_IO0
    PF9     ------> QUADSPI_BK1_IO1
    PB2     ------> QUADSPI_CLK
    PB6     ------> QUADSPI_BK1_NCS
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2|GPIO_PIN_6);

    /* QUADSPI interrupt Deinit */
    HAL_NVIC_DisableIRQ(QUADSPI_IRQn);
  /* USER CODE BEGIN QUADSPI_MspDeInit 1 */

  /* USER CODE END QUADSPI_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/* QUADSPI init function */
uint8_t CSP_QUADSPI_Init(void) {
  // prepare QSPI peripheral for ST-Link Utility operations
  hqspi.Instance = QUADSPI;
  QPI_Mode_Enabled_Flag = 0;
  if (HAL_QSPI_DeInit(&hqspi) != HAL_OK) {
    return HAL_ERROR;
  }

  MX_QUADSPI_Init();

  // QSPI_QPIModeDisable();

  if (QSPI_ResetChip() != HAL_OK) {
    return HAL_ERROR;
  }

  HAL_Delay(1);

  if (QSPI_QPIModeEnable() != HAL_OK) {
    return HAL_ERROR;
  }

  if (QSPI_AutoPollingMemReady() != HAL_OK) {
    return HAL_ERROR;
  }

  if (QSPI_WriteEnable() != HAL_OK) {

    return HAL_ERROR;
  }

  if (QSPI_Configuration() != HAL_OK) {
    return HAL_ERROR;
  }

  return HAL_OK;
}

uint8_t CSP_QSPI_Erase_Chip(void) {
  QSPI_CommandTypeDef sCommand;

  /* Erasing Sequence --------------------------------- */
  if (QPI_Mode_Enabled_Flag) {
    sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
    // sCommand.DataMode = QSPI_DATA_4_LINES;
  } else {
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    // sCommand.DataMode = QSPI_DATA_1_LINE;
  }
  sCommand.Instruction = CHIP_ERASE_CMD;
  // sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  sCommand.DataMode = QSPI_DATA_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_NONE;
  sCommand.Address = 0;
  sCommand.DummyCycles = 0;

  if (QSPI_WriteEnable() != HAL_OK) {
    return HAL_ERROR;
  }

  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }

  if (QSPI_AutoPollingMemReady() != HAL_OK) {
    return HAL_ERROR;
  }

  return HAL_OK;
}

uint8_t QSPI_AutoPollingMemReady(void) {
  QSPI_CommandTypeDef sCommand;
  QSPI_AutoPollingTypeDef sConfig;

  /* Configure automatic polling mode to wait for memory ready ------ */
  if (QPI_Mode_Enabled_Flag) {
    sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
    sCommand.DataMode = QSPI_DATA_4_LINES;
  } else {
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.DataMode = QSPI_DATA_1_LINE;
  }

  // sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction = READ_STATUS_REG_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  // sCommand.DataMode = QSPI_DATA_4_LINES;
  sCommand.DummyCycles = 0;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.NbData = 1;

  sConfig.Match = 0x00;
  sConfig.Mask = 0x01;
  sConfig.MatchMode = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval = 0x10;
  sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig,
                           HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
    return HAL_ERROR;
  }

  return HAL_OK;
}

static uint8_t QSPI_WriteEnable(void) {
  QSPI_CommandTypeDef sCommand;
  QSPI_AutoPollingTypeDef sConfig;

  /* Enable write operations ------------------------------------------ */
  if (QPI_Mode_Enabled_Flag) {
    sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
    // sCommand.DataMode = QSPI_DATA_4_LINES;
  } else {
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    // sCommand.DataMode = QSPI_DATA_1_LINE;
  }

  sCommand.Instruction = WRITE_ENABLE_CMD;
  sCommand.DataMode = QSPI_DATA_NONE;
  sCommand.AddressMode = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DummyCycles = 0;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }

  /* Configure automatic polling mode to wait for write enabling ---- */
  sConfig.Match = 0x02;
  sConfig.Mask = 0x02;
  sConfig.MatchMode = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval = 0x10;
  sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

  sCommand.Instruction = READ_STATUS_REG_CMD;
  sCommand.NbData = 1;
  // sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  if (QPI_Mode_Enabled_Flag) {
    sCommand.DataMode = QSPI_DATA_4_LINES;
  } else {
    sCommand.DataMode = QSPI_DATA_1_LINE;
  }

  if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig,
                           HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
    return HAL_ERROR;
  }

  return HAL_OK;
}

static uint8_t QSPI_QPIModeEnable(void) {
  QSPI_CommandTypeDef sCommand;
  uint8_t reg;

  /* Read out value of Status Resister 2 ---------------------- */
  sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction = READ_STATUS_REG2_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode = QSPI_DATA_1_LINE;
  sCommand.NbData = 1;
  sCommand.DummyCycles = 0;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }

  if (HAL_QSPI_Receive(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }

  if ((reg & 0X02) == 0) {
    reg |= 1 << 1;

    sCommand.Instruction = WRITE_STATUS_REG2_CMD;
    sCommand.DataMode = QSPI_DATA_1_LINE;

    if (QSPI_WriteEnable() != HAL_OK) {
      return HAL_ERROR;
    }
    if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
        HAL_OK) {
      return HAL_ERROR;
    }

    if (HAL_QSPI_Transmit(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
        HAL_OK) {
      Error_Handler();
      return HAL_ERROR;
    }
  }

  /* Enable QPI mode ------------------------------------------ */
  sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction = ENTER_QPI_MODE_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode = QSPI_DATA_NONE;
  sCommand.DummyCycles = 0;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  if (QSPI_WriteEnable() != HAL_OK) {
    return HAL_ERROR;
  }

  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }

  HAL_Delay(1);

  /* Read out value of Status Resister 2 ---------------------- */
  sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
  sCommand.Instruction = READ_STATUS_REG2_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode = QSPI_DATA_4_LINES;
  sCommand.NbData = 1;
  sCommand.DummyCycles = 0;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }

  if (HAL_QSPI_Receive(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }

  if ((reg & 0X02) == 0) {
    return HAL_ERROR;
  }

  QPI_Mode_Enabled_Flag = 1;

  return HAL_OK;
}

// static uint8_t QSPI_QPIModeDisable(void)
//{
//    QSPI_CommandTypeDef sCommand;
//
//    /* Exit QPI mode ------------------------------------------ */
//    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
//    sCommand.Instruction = EXIT_QPI_MODE_CMD;
//    sCommand.AddressMode = QSPI_ADDRESS_NONE;
//    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
//    sCommand.DataMode = QSPI_DATA_4_LINES;
//    sCommand.DummyCycles = 0;
//    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
//    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
//    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
//
//    if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
//    HAL_OK)
//    {
//        return HAL_ERROR;
//    }
//
//    return HAL_OK;
//}

/*Enable quad mode and set dummy cycles count*/
uint8_t QSPI_Configuration(void) {

  QSPI_CommandTypeDef sCommand;
  uint8_t reg = 3 << 4;

  /*enter 4 byte address*/
  sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
  sCommand.Instruction = ENTER_4_BYTE_ADD_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode = QSPI_DATA_NONE;
  sCommand.DummyCycles = 0;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  if (QSPI_WriteEnable() != HAL_OK) {
    return HAL_ERROR;
  }

  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }

  sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
  sCommand.Instruction = WRITE_VOL_CFG_REG_CMD;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_NONE;
  sCommand.DataMode = QSPI_DATA_4_LINES;
  sCommand.DummyCycles = 0;
  sCommand.NbData = 1;

  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }

  if (HAL_QSPI_Transmit(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    Error_Handler();
    return HAL_ERROR;
  }
  return HAL_OK;
}

uint8_t CSP_QSPI_EraseSector(uint32_t EraseStartAddress,
                             uint32_t EraseEndAddress) {

  QSPI_CommandTypeDef sCommand;

  EraseStartAddress =
      EraseStartAddress - EraseStartAddress % MEMORY_SECTOR_SIZE;

  /* Erasing Sequence -------------------------------------------------- */
  sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
  sCommand.Instruction = SECTOR_ERASE_CMD;
  sCommand.AddressSize = QSPI_ADDRESS_32_BITS;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
  sCommand.DataMode = QSPI_DATA_NONE;
  sCommand.DummyCycles = 0;

  while (EraseEndAddress >= EraseStartAddress) {
    sCommand.Address = (EraseStartAddress & 0x0FFFFFFF);

    if (QSPI_WriteEnable() != HAL_OK) {
      return HAL_ERROR;
    }

    if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
        HAL_OK) {
      return HAL_ERROR;
    }
    EraseStartAddress += MEMORY_SECTOR_SIZE;

    if (QSPI_AutoPollingMemReady() != HAL_OK) {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

uint8_t CSP_QSPI_WriteMemory(uint8_t *buffer, uint32_t address,
                             uint32_t buffer_size) {

  QSPI_CommandTypeDef sCommand;
  uint32_t end_addr, current_size, current_addr;

  /* Calculation of the size between the write address and the end of the page
   */
  current_addr = 0;

  while (current_addr <= address) {
    current_addr += MEMORY_PAGE_SIZE;
  }
  current_size = current_addr - address;

  /* Check if the size of the data is less than the remaining place in the page
   */
  if (current_size > buffer_size) {
    current_size = buffer_size;
  }

  /* Initialize the adress variables */
  current_addr = address;
  end_addr = address + buffer_size;

  sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
  sCommand.Instruction = QUAD_IN_FAST_PROG_CMD;
  sCommand.AddressSize = QSPI_ADDRESS_32_BITS;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
  sCommand.DataMode = QSPI_DATA_4_LINES;
  sCommand.NbData = buffer_size;
  sCommand.Address = address;
  sCommand.DummyCycles = 0;

  /* Perform the write page by page */
  do {
    sCommand.Address = current_addr;
    sCommand.NbData = current_size;

    if (current_size == 0) {
      return HAL_OK;
    }

    /* Enable write operations */
    if (QSPI_WriteEnable() != HAL_OK) {
      return HAL_ERROR;
    }

    /* Configure the command */
    if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
        HAL_OK) {

      return HAL_ERROR;
    }

    /* Transmission of the data */
    if (HAL_QSPI_Transmit(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
        HAL_OK) {

      return HAL_ERROR;
    }

    /* Configure automatic polling mode to wait for end of program */
    if (QSPI_AutoPollingMemReady() != HAL_OK) {
      return HAL_ERROR;
    }

    /* Update the address and size variables for next page programming */
    current_addr += current_size;
    buffer += current_size;
    current_size = ((current_addr + MEMORY_PAGE_SIZE) > end_addr)
                       ? (end_addr - current_addr)
                       : MEMORY_PAGE_SIZE;
  } while (current_addr <= end_addr);

  return HAL_OK;
}

uint8_t CSP_QSPI_ReadMemory(uint8_t *buffer, uint32_t address,
                            uint32_t buffer_size) {
  QSPI_CommandTypeDef sCommand;

  sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
  sCommand.Instruction = QUAD_OUT_FAST_READ_CMD;
  sCommand.AddressSize = QSPI_ADDRESS_32_BITS;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
  sCommand.DataMode = QSPI_DATA_4_LINES;
  sCommand.NbData = buffer_size;
  sCommand.Address = address;
  sCommand.DummyCycles = 8;

  /* Configure the command */
  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {

    return HAL_ERROR;
  }

  if (HAL_QSPI_Receive(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }

  return HAL_OK;
}

uint8_t CSP_QSPI_EnableMemoryMappedMode(void) {

  QSPI_CommandTypeDef sCommand;
  QSPI_MemoryMappedTypeDef sMemMappedCfg;

  /* Enable Memory-Mapped mode--------------------------------------------------
   */

  sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
  sCommand.Instruction = QUAD_OUT_FAST_READ_CMD;
  sCommand.AddressSize = QSPI_ADDRESS_32_BITS;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
  sCommand.DataMode = QSPI_DATA_4_LINES;
  sCommand.NbData = 0;
  sCommand.Address = 0;
  sCommand.DummyCycles = 8;

  sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
  // sMemMappedCfg.TimeOutPeriod = 0;

  if (HAL_QSPI_MemoryMapped(&hqspi, &sCommand, &sMemMappedCfg) != HAL_OK) {
    return HAL_ERROR;
  }
  return HAL_OK;
}

uint8_t QSPI_ResetChip() {
  QSPI_CommandTypeDef sCommand;
  uint32_t temp = 0;

  /* Erasing Sequence -------------------------------------------------- */
  sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction = RESET_ENABLE_CMD;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_NONE;
  sCommand.Address = 0;
  sCommand.DataMode = QSPI_DATA_NONE;
  sCommand.DummyCycles = 0;

  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }
  for (temp = 0; temp < 0x2f; temp++) {
    __NOP();
  }

  sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction = RESET_EXECUTE_CMD;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_NONE;
  sCommand.Address = 0;
  sCommand.DataMode = QSPI_DATA_NONE;
  sCommand.DummyCycles = 0;

  if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) !=
      HAL_OK) {
    return HAL_ERROR;
  }
  return HAL_OK;
}

void vApp_User_QSPI_Configuration(void) {
  if (CSP_QUADSPI_Init() != HAL_OK) {
    Error_Handler();
  }
  if (CSP_QSPI_EnableMemoryMappedMode() != HAL_OK) {
    Error_Handler();
  }
}
/* USER CODE END 1 */
