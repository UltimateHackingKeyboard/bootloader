var group__spi =
[
    [ "spi_master_config_t", "group__spi.html#structspi__master__config__t", [
      [ "baudRate_Bps", "group__spi.html#aa5df547b4cb95d3c959373cf6fa672b5", null ],
      [ "dataMode", "group__spi.html#ac19bf21df94096b28f0cf83f277a91b0", null ],
      [ "direction", "group__spi.html#ae8f40fc982ba997f08e6a1fe1fe8fd8c", null ],
      [ "enableFifoInterruptClear", "group__spi.html#af7e84b7c37b316924205ce9d9f0ec685", null ],
      [ "enableMaster", "group__spi.html#ab8b96ba3ced8b280ac1f366f6e76a9e7", null ],
      [ "enableStopInWaitMode", "group__spi.html#a9b8027e0bd0a21915f56155fdc08c5fc", null ],
      [ "outputMode", "group__spi.html#a285cf929f1817b37a10f2afffc810ac8", null ],
      [ "phase", "group__spi.html#af7cf10baeb58ef18f8d18ef7022d43d8", null ],
      [ "pinMode", "group__spi.html#ab929baca49507045ca23069da9bbe3ba", null ],
      [ "polarity", "group__spi.html#ad5743b187f5dda0c1786a192ba11b043", null ],
      [ "rxWatermark", "group__spi.html#a0190e6775edf2ecbae497859f514760f", null ],
      [ "txWatermark", "group__spi.html#ab4b6047acff1c6e74f90b6e75492295a", null ]
    ] ],
    [ "spi_slave_config_t", "group__spi.html#structspi__slave__config__t", [
      [ "dataMode", "group__spi.html#ac19bf21df94096b28f0cf83f277a91b0", null ],
      [ "direction", "group__spi.html#ae8f40fc982ba997f08e6a1fe1fe8fd8c", null ],
      [ "enableFifoInterruptClear", "group__spi.html#af7e84b7c37b316924205ce9d9f0ec685", null ],
      [ "enableSlave", "group__spi.html#a9189d8f6438ba99548837da162213c46", null ],
      [ "enableStopInWaitMode", "group__spi.html#a9b8027e0bd0a21915f56155fdc08c5fc", null ],
      [ "phase", "group__spi.html#af7cf10baeb58ef18f8d18ef7022d43d8", null ],
      [ "polarity", "group__spi.html#ad5743b187f5dda0c1786a192ba11b043", null ],
      [ "rxWatermark", "group__spi.html#a0190e6775edf2ecbae497859f514760f", null ],
      [ "txWatermark", "group__spi.html#ab4b6047acff1c6e74f90b6e75492295a", null ]
    ] ],
    [ "spi_transfer_t", "group__spi.html#structspi__transfer__t", [
      [ "dataSize", "group__spi.html#a78f9703861dd365a513c2c5aab9f9239", null ],
      [ "flags", "group__spi.html#a773b39d480759f67926cb18ae2219281", null ],
      [ "rxData", "group__spi.html#ab83c0e07099df7beb8e491cb91914de0", null ],
      [ "txData", "group__spi.html#a03c054bb486fb65133eb9f6849266fb1", null ]
    ] ],
    [ "spi_master_handle_t", "group__spi.html#struct__spi__master__handle", [
      [ "bytePerFrame", "group__spi.html#a91e259e32d8fb8a07db35bb933c2b6a4", null ],
      [ "callback", "group__spi.html#a080452bbb72856f9fc2e834d6537d9ff", null ],
      [ "rxData", "group__spi.html#aa58335de5bfa8923228432b62ea9308a", null ],
      [ "rxRemainingBytes", "group__spi.html#aa7189218ccadddcc71ad7de6b758f01a", null ],
      [ "state", "group__spi.html#a47e491dc6b16e7a86f4396620f4bb704", null ],
      [ "transferSize", "group__spi.html#a10e6d1f095e525fa85ffe957081ed7a7", null ],
      [ "txData", "group__spi.html#ab56d8f300582ce9d7f4a79729124739d", null ],
      [ "txRemainingBytes", "group__spi.html#a554cc5b5619072f7256a7f7cc1f2bcdb", null ],
      [ "userData", "group__spi.html#a2e294dd14122c554baa0665072b4ca7a", null ],
      [ "watermark", "group__spi.html#a3585201b190b39d2d702daa9192323a3", null ]
    ] ],
    [ "spi_master_callback_t", "group__spi.html#ga75d9df6e4614756d8ff1bd6f86ca2235", null ],
    [ "spi_slave_callback_t", "group__spi.html#ga13fbc3110c56c1d312e4a5ebed07d679", null ],
    [ "spi_slave_handle_t", "group__spi.html#gad267cfee3a876b2860217ff94f03f574", null ],
    [ "_spi_dma_enable_t", "group__spi.html#ga8ab1fba361ce972e7e249ba1ea318e20", [
      [ "kSPI_TxDmaEnable", "group__spi.html#gga8ab1fba361ce972e7e249ba1ea318e20a0bbf1c58480329e906e2b80a05121cc5", null ],
      [ "kSPI_RxDmaEnable", "group__spi.html#gga8ab1fba361ce972e7e249ba1ea318e20a0addd2d49971cb0f0caa057510f5d9f1", null ],
      [ "kSPI_DmaAllEnable", "group__spi.html#gga8ab1fba361ce972e7e249ba1ea318e20aa157e1fb5d95f1488f6f03fb4baaa7f2", null ]
    ] ],
    [ "_spi_flags", "group__spi.html#gaea776f478792865a85b7311e6ff5896c", [
      [ "kSPI_RxBufferFullFlag", "group__spi.html#ggaea776f478792865a85b7311e6ff5896cacc0e5c67e296cc20197afaca46f22953", null ],
      [ "kSPI_MatchFlag", "group__spi.html#ggaea776f478792865a85b7311e6ff5896ca9c24fe83960ed64638f06eeb17643da5", null ],
      [ "kSPI_TxBufferEmptyFlag", "group__spi.html#ggaea776f478792865a85b7311e6ff5896ca07934a27954d951831e7cdb96c39afd7", null ],
      [ "kSPI_ModeFaultFlag", "group__spi.html#ggaea776f478792865a85b7311e6ff5896ca9eca4e759c879e3b264d052c234a09d1", null ],
      [ "kSPI_RxFifoNearFullFlag", "group__spi.html#ggaea776f478792865a85b7311e6ff5896ca840b49c37a729e29d6c144650f31dc88", null ],
      [ "kSPI_TxFifoNearEmptyFlag", "group__spi.html#ggaea776f478792865a85b7311e6ff5896ca85cc9ec1f4395db09fc288e293e5dcb1", null ],
      [ "kSPI_RxFifoFullFlag", "group__spi.html#ggaea776f478792865a85b7311e6ff5896ca1ad600ec61b202731d386c7abcb15feb", null ],
      [ "kSPI_TxFifoEmptyFlag", "group__spi.html#ggaea776f478792865a85b7311e6ff5896ca275d9a4cd902b8cb484c4b00635a3060", null ],
      [ "kSPI_TxFifoError", "group__spi.html#ggaea776f478792865a85b7311e6ff5896cab1d47ff1dc06aa27a41cf90715f203aa", null ],
      [ "kSPI_RxFifoError", "group__spi.html#ggaea776f478792865a85b7311e6ff5896ca46b6a3bffe664d731bfbfa38f24a5797", null ],
      [ "kSPI_TxOverflow", "group__spi.html#ggaea776f478792865a85b7311e6ff5896ca553c7d65e38657565d1818fdfddd600e", null ],
      [ "kSPI_RxOverflow", "group__spi.html#ggaea776f478792865a85b7311e6ff5896ca92f9ace674410eacc7f5a1bdbbdac23c", null ]
    ] ],
    [ "_spi_interrupt_enable", "group__spi.html#gaedd690a0f91a0a9eb0fd573b57e31f67", [
      [ "kSPI_RxFullAndModfInterruptEnable", "group__spi.html#ggaedd690a0f91a0a9eb0fd573b57e31f67aa317b77c827ed1462b766dddd93f7f10", null ],
      [ "kSPI_TxEmptyInterruptEnable", "group__spi.html#ggaedd690a0f91a0a9eb0fd573b57e31f67abe157750a1660d839a66197c56ac5096", null ],
      [ "kSPI_MatchInterruptEnable", "group__spi.html#ggaedd690a0f91a0a9eb0fd573b57e31f67a95cc9167ada10046534dc22549c6a99e", null ],
      [ "kSPI_RxFifoNearFullInterruptEnable", "group__spi.html#ggaedd690a0f91a0a9eb0fd573b57e31f67a081a753d8d51b97b289103c698703537", null ],
      [ "kSPI_TxFifoNearEmptyInterruptEnable", "group__spi.html#ggaedd690a0f91a0a9eb0fd573b57e31f67a299b7d97e4106d57bf06a6654ce4f3dd", null ]
    ] ],
    [ "_spi_status", "group__spi.html#ga3fa79a6717ea4e1e74de2dadaa468edd", [
      [ "kStatus_SPI_Busy", "group__spi.html#gga3fa79a6717ea4e1e74de2dadaa468edda703abdf7900047c4d13536480f3463ab", null ],
      [ "kStatus_SPI_Idle", "group__spi.html#gga3fa79a6717ea4e1e74de2dadaa468edda4e32c5b06dccaf4b81e2fd1679e1b560", null ],
      [ "kStatus_SPI_Error", "group__spi.html#gga3fa79a6717ea4e1e74de2dadaa468edda2ff91d774e93aed936b87ffaa18aaf9e", null ]
    ] ],
    [ "spi_clock_phase_t", "group__spi.html#ga9ad313685ade497f5cbcb71c74a1b4dc", [
      [ "kSPI_ClockPhaseFirstEdge", "group__spi.html#gga9ad313685ade497f5cbcb71c74a1b4dcad15d61c6fd642f13101edbf401d0c72e", null ],
      [ "kSPI_ClockPhaseSecondEdge", "group__spi.html#gga9ad313685ade497f5cbcb71c74a1b4dca18a98985c1f7dd56175e4a2724db3675", null ]
    ] ],
    [ "spi_clock_polarity_t", "group__spi.html#ga3e5a7cd043c9596779bc23b34cb3d1f9", [
      [ "kSPI_ClockPolarityActiveHigh", "group__spi.html#gga3e5a7cd043c9596779bc23b34cb3d1f9a031c0ee2693cf1fd621e8b8cba676629", null ],
      [ "kSPI_ClockPolarityActiveLow", "group__spi.html#gga3e5a7cd043c9596779bc23b34cb3d1f9acfc8257079c9604086622df6de326aea", null ]
    ] ],
    [ "spi_data_bitcount_mode_t", "group__spi.html#gaa7bfe75c1f0ea3b349f19a3de19b24e4", [
      [ "kSPI_8BitMode", "group__spi.html#ggaa7bfe75c1f0ea3b349f19a3de19b24e4a1a0723fd8cd73f361ca2770ad74a6324", null ],
      [ "kSPI_16BitMode", "group__spi.html#ggaa7bfe75c1f0ea3b349f19a3de19b24e4a740c43589ebe839f3adc77b8ca484ea4", null ]
    ] ],
    [ "spi_pin_mode_t", "group__spi.html#gab55fee4d636428392047e3355f33a36f", [
      [ "kSPI_PinModeNormal", "group__spi.html#ggab55fee4d636428392047e3355f33a36fa7ba3d5ffce8458f91a9594e7ffe2b32d", null ],
      [ "kSPI_PinModeInput", "group__spi.html#ggab55fee4d636428392047e3355f33a36fad778c9cc9e3d5a5c4e8061793cf50fdc", null ],
      [ "kSPI_PinModeOutput", "group__spi.html#ggab55fee4d636428392047e3355f33a36fad5b79c8eba688dbfb4b9973348521de7", null ]
    ] ],
    [ "spi_rxfifo_watermark_t", "group__spi.html#ga79f862820ec2bcbb8184ce9de72949a6", [
      [ "kSPI_RxFifoThreeFourthsFull", "group__spi.html#gga79f862820ec2bcbb8184ce9de72949a6ad045f28c12abb7d7c9c69f067d03efb2", null ],
      [ "kSPI_RxFifoOneHalfFull", "group__spi.html#gga79f862820ec2bcbb8184ce9de72949a6aa10222f6949d379dfaf8f408bbb87c42", null ]
    ] ],
    [ "spi_shift_direction_t", "group__spi.html#gaa68518c16202382c2e1f1c7c66a9d53d", [
      [ "kSPI_MsbFirst", "group__spi.html#ggaa68518c16202382c2e1f1c7c66a9d53dae7b997e8cff761aab865cbd42c4c3989", null ],
      [ "kSPI_LsbFirst", "group__spi.html#ggaa68518c16202382c2e1f1c7c66a9d53da20ac53684c3e1ad338553cecbfab94a9", null ]
    ] ],
    [ "spi_ss_output_mode_t", "group__spi.html#ga2e5a238c65f35a2d82cc1c55927030fe", [
      [ "kSPI_SlaveSelectAsGpio", "group__spi.html#gga2e5a238c65f35a2d82cc1c55927030fea3825177650b5d4bfb5dc603f0ce41381", null ],
      [ "kSPI_SlaveSelectFaultInput", "group__spi.html#gga2e5a238c65f35a2d82cc1c55927030feafdcbdc624d6c2f057147e2aa3cae4635", null ],
      [ "kSPI_SlaveSelectAutomaticOutput", "group__spi.html#gga2e5a238c65f35a2d82cc1c55927030fead724fc04589d03b524ef2dfef6b0f4a1", null ]
    ] ],
    [ "spi_txfifo_watermark_t", "group__spi.html#ga9a479127a2051ded7945115657adc162", [
      [ "kSPI_TxFifoOneFourthEmpty", "group__spi.html#gga9a479127a2051ded7945115657adc162a9349658226a7cb7eb0629ae38853030d", null ],
      [ "kSPI_TxFifoOneHalfEmpty", "group__spi.html#gga9a479127a2051ded7945115657adc162a1460af596f3d1a6a2bbedd9624975ed5", null ]
    ] ],
    [ "spi_w1c_interrupt_t", "group__spi.html#gad61329dc7edac1f4ef75e0746e08b3d1", [
      [ "kSPI_RxFifoFullClearInterrupt", "group__spi.html#ggad61329dc7edac1f4ef75e0746e08b3d1a1ee9a347a93f3a74a8c72786747f2a22", null ],
      [ "kSPI_TxFifoEmptyClearInterrupt", "group__spi.html#ggad61329dc7edac1f4ef75e0746e08b3d1adc9f4730672a8501f0ae14b25f044567", null ],
      [ "kSPI_RxNearFullClearInterrupt", "group__spi.html#ggad61329dc7edac1f4ef75e0746e08b3d1af3a8b77f84cf2406ed1365e02e74fa8a", null ],
      [ "kSPI_TxNearEmptyClearInterrupt", "group__spi.html#ggad61329dc7edac1f4ef75e0746e08b3d1ac5358e4b6907d9db9ec2eb5122f1e15c", null ]
    ] ],
    [ "SPI_ClearInterrupt", "group__spi.html#ga57d32103b22e375efde0d1a392f125ea", null ],
    [ "SPI_Deinit", "group__spi.html#gaac0bc2b87ea2eb7eeba78d9449d4dbbf", null ],
    [ "SPI_DisableInterrupts", "group__spi.html#ga1c3de83156f45d3f91540a1ec5f92826", null ],
    [ "SPI_Enable", "group__spi.html#gaae5df847701d3171c2e6787b33e2f1ed", null ],
    [ "SPI_EnableDMA", "group__spi.html#ga552ce373bfe655a37a22c26fdb071e0b", null ],
    [ "SPI_EnableFIFO", "group__spi.html#ga73f02aa76d813feff22fb3855105e023", null ],
    [ "SPI_EnableInterrupts", "group__spi.html#gac12d144816080c40ca86d762e31aacc4", null ],
    [ "SPI_GetDataRegisterAddress", "group__spi.html#ga740215d83c1238818dfd4689163f71de", null ],
    [ "SPI_GetStatusFlags", "group__spi.html#gaaa5a317a68b409dfe20397b45e48d1f0", null ],
    [ "SPI_MasterGetDefaultConfig", "group__spi.html#ga45c08fc078ae334b79fb844379140838", null ],
    [ "SPI_MasterInit", "group__spi.html#ga3fe5b421b088cc98222b8a214069574b", null ],
    [ "SPI_MasterSetBaudRate", "group__spi.html#ga3ebe045018782edb3624026795d6269a", null ],
    [ "SPI_MasterTransferAbort", "group__spi.html#gae90962a54978acf05ca7780489301eb4", null ],
    [ "SPI_MasterTransferBlocking", "group__spi.html#ga5b05095245ecf01258e64cc0458fb2e9", null ],
    [ "SPI_MasterTransferCreateHandle", "group__spi.html#ga6cf3e807307ecb22578cc9088adafcf2", null ],
    [ "SPI_MasterTransferGetCount", "group__spi.html#gabde0dccfb0783d103b9cf57e0202582f", null ],
    [ "SPI_MasterTransferHandleIRQ", "group__spi.html#ga645d041a92bde312d6cf64517c618c41", null ],
    [ "SPI_MasterTransferNonBlocking", "group__spi.html#ga820c78a32fa29735168d2e517f4881a1", null ],
    [ "SPI_ReadData", "group__spi.html#gaf23d3779b122e78fc07562bf5dbf3ac3", null ],
    [ "SPI_SetMatchData", "group__spi.html#ga981b773ced8cc0df2493691842a14e05", null ],
    [ "SPI_SlaveGetDefaultConfig", "group__spi.html#gac000b63ed033f57a9eee342a8c8e67f2", null ],
    [ "SPI_SlaveInit", "group__spi.html#ga91b214b5392fc8d5b73a5ebadc5ca363", null ],
    [ "SPI_SlaveTransferAbort", "group__spi.html#gae719048431a3e4fb334f83bd824a407b", null ],
    [ "SPI_SlaveTransferCreateHandle", "group__spi.html#ga7b96130e93f13360909634c8fd5989b2", null ],
    [ "SPI_SlaveTransferGetCount", "group__spi.html#ga0dcd2ed8373d992ff93bb500e1442815", null ],
    [ "SPI_SlaveTransferHandleIRQ", "group__spi.html#gabf454f42532e8a41340efd398f9868fb", null ],
    [ "SPI_SlaveTransferNonBlocking", "group__spi.html#gae37917cb354e36acd1b1ca906d2ffe1c", null ],
    [ "SPI_WriteBlocking", "group__spi.html#gae28a41ba015e3bc92936459f83500cd0", null ],
    [ "SPI_WriteData", "group__spi.html#ga74d8732386a607c263bd16c8294b08d6", null ]
];