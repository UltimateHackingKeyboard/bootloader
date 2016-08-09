var group__lpi2c__slave__driver =
[
    [ "lpi2c_slave_config_t", "group__lpi2c__slave__driver.html#structlpi2c__slave__config__t", [
      [ "address0", "group__lpi2c__slave__driver.html#aff9b3a49968d57ad40dd16396771a9fc", null ],
      [ "address1", "group__lpi2c__slave__driver.html#a543aac749a1a6c5979078c37746dc889", null ],
      [ "addressMatchMode", "group__lpi2c__slave__driver.html#a3af8f35baf0b56703fd4f5faade04fca", null ],
      [ "clockHoldTime_ns", "group__lpi2c__slave__driver.html#abf8acbf844a6a2bee1eb187b90fc65c3", null ],
      [ "dataValidDelay_ns", "group__lpi2c__slave__driver.html#a0c0a9a010bd402a3d8a2e4028c513737", null ],
      [ "enableGeneralCall", "group__lpi2c__slave__driver.html#aedb9cfa838d8a677d9193d5c92298ea4", null ],
      [ "enableReceivedAddressRead", "group__lpi2c__slave__driver.html#a72320d119698767e7b2a424f41a39fbc", null ],
      [ "enableSlave", "group__lpi2c__slave__driver.html#a9189d8f6438ba99548837da162213c46", null ],
      [ "filterDozeEnable", "group__lpi2c__slave__driver.html#a936b2fb7962b6f10143cac2cf270745a", null ],
      [ "filterEnable", "group__lpi2c__slave__driver.html#a4d535e193da676b2da47c3e956a8bd56", null ],
      [ "ignoreAck", "group__lpi2c__slave__driver.html#a0c9caf9d8740154459a3cdff687e8d3c", null ],
      [ "sclGlitchFilterWidth_ns", "group__lpi2c__slave__driver.html#a712c8bd76a60c235b6b3d8de0bde4731", null ],
      [ "sclStall", "group__lpi2c__slave__driver.html#a4cd890a471a4317e11d6052d6073cc43", null ],
      [ "sdaGlitchFilterWidth_ns", "group__lpi2c__slave__driver.html#af927e91c011fa7491aef7ada886518f8", null ]
    ] ],
    [ "lpi2c_slave_config_t.sclStall", "group__lpi2c__slave__driver.html#structlpi2c__slave__config__t_8scl_stall", [
      [ "enableAck", "group__lpi2c__slave__driver.html#a409481c59d122c0997eef20ef1f47a52", null ],
      [ "enableAddress", "group__lpi2c__slave__driver.html#abdc94b49613b81994ae0fa4803e36bc1", null ],
      [ "enableRx", "group__lpi2c__slave__driver.html#a9ef10d943a85eb899cdf2826c7c3a2bc", null ],
      [ "enableTx", "group__lpi2c__slave__driver.html#a395a5d14341597d7b707514605b15c9d", null ]
    ] ],
    [ "lpi2c_slave_transfer_t", "group__lpi2c__slave__driver.html#structlpi2c__slave__transfer__t", [
      [ "completionStatus", "group__lpi2c__slave__driver.html#aac6aa92f2aef99293ab2f5ad6f734fad", null ],
      [ "data", "group__lpi2c__slave__driver.html#abe222f6d3581e7920dcad5306cc906a8", null ],
      [ "dataSize", "group__lpi2c__slave__driver.html#a78f9703861dd365a513c2c5aab9f9239", null ],
      [ "event", "group__lpi2c__slave__driver.html#a316e6109eb033d9398c142e2c071383f", null ],
      [ "receivedAddress", "group__lpi2c__slave__driver.html#ae32359c3b68622d1de64c0c3e5cd2542", null ],
      [ "transferredCount", "group__lpi2c__slave__driver.html#a97856cb5d71b7981d4ce9813124a5433", null ]
    ] ],
    [ "lpi2c_slave_handle_t", "group__lpi2c__slave__driver.html#struct__lpi2c__slave__handle", [
      [ "callback", "group__lpi2c__slave__driver.html#a0bc069bcca574b2ce717aa640cb47439", null ],
      [ "eventMask", "group__lpi2c__slave__driver.html#acf2922a79dce3fb9f7c7fe948de1f5a8", null ],
      [ "isBusy", "group__lpi2c__slave__driver.html#a099f725f22a344e190121634f53328d8", null ],
      [ "transfer", "group__lpi2c__slave__driver.html#a60922e422a33982a7db7888ab3072d6a", null ],
      [ "transferredCount", "group__lpi2c__slave__driver.html#abff366b77633e9abbfc21db3fbd8caf9", null ],
      [ "userData", "group__lpi2c__slave__driver.html#a2e294dd14122c554baa0665072b4ca7a", null ],
      [ "wasTransmit", "group__lpi2c__slave__driver.html#a0db88bc215e9540584951267e595103f", null ]
    ] ],
    [ "lpi2c_slave_transfer_callback_t", "group__lpi2c__slave__driver.html#gaddf93dfdcc63952d562a61e5631f31ad", null ],
    [ "_lpi2c_slave_flags", "group__lpi2c__slave__driver.html#gabd50effc706692c03b42faa72c34269b", [
      [ "kLPI2C_SlaveTxReadyFlag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269ba80486f66e12276c945b8813269b90c0e", null ],
      [ "kLPI2C_SlaveRxReadyFlag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269ba01265ce6645e4a978b823b1f130a419f", null ],
      [ "kLPI2C_SlaveAddressValidFlag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269baf34a60fee419e0b3d387b353a38b4772", null ],
      [ "kLPI2C_SlaveTransmitAckFlag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269ba37386d33a28e37352a8e3151f027fdff", null ],
      [ "kLPI2C_SlaveRepeatedStartDetectFlag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269ba5c5dcad526309c44aa390c13ae53ca3e", null ],
      [ "kLPI2C_SlaveStopDetectFlag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269baaaa1d719607915d0b1251727900018a7", null ],
      [ "kLPI2C_SlaveBitErrFlag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269ba41375eeb82c399aff15daba1e8bbff03", null ],
      [ "kLPI2C_SlaveFifoErrFlag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269ba6eb9dd96bad287dcb7e2f23f73d961a8", null ],
      [ "kLPI2C_SlaveAddressMatch0Flag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269ba9fb3f57d810e280effee1dae37d062bb", null ],
      [ "kLPI2C_SlaveAddressMatch1Flag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269ba62cc9694d6891b21af074122eeedca85", null ],
      [ "kLPI2C_SlaveGeneralCallFlag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269ba6a0fa821b530336ea8d1f19aadcbe1dc", null ],
      [ "kLPI2C_SlaveBusyFlag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269baffa3195deae58fc6ea15d062b465ac5d", null ],
      [ "kLPI2C_SlaveBusBusyFlag", "group__lpi2c__slave__driver.html#ggabd50effc706692c03b42faa72c34269ba2531ffa96faa3086714e8a069508867b", null ]
    ] ],
    [ "lpi2c_slave_address_match_t", "group__lpi2c__slave__driver.html#gac3564395ccab19eb1ce6ab46b36bb5bb", [
      [ "kLPI2C_MatchAddress0", "group__lpi2c__slave__driver.html#ggac3564395ccab19eb1ce6ab46b36bb5bbaaa16a731881882d10f48ebde416f54c5", null ],
      [ "kLPI2C_MatchAddress0OrAddress1", "group__lpi2c__slave__driver.html#ggac3564395ccab19eb1ce6ab46b36bb5bba2941f8a06a17205294e7d0fa5f305675", null ],
      [ "kLPI2C_MatchAddress0ThroughAddress1", "group__lpi2c__slave__driver.html#ggac3564395ccab19eb1ce6ab46b36bb5bba59e460fdd7075191f69e047ef35557eb", null ]
    ] ],
    [ "lpi2c_slave_transfer_event_t", "group__lpi2c__slave__driver.html#ga0d99b4dba3841a4e02f7c431a59006c8", [
      [ "kLPI2C_SlaveAddressMatchEvent", "group__lpi2c__slave__driver.html#gga0d99b4dba3841a4e02f7c431a59006c8a10fb8d9bb6ba9cd44fde85466e6eabef", null ],
      [ "kLPI2C_SlaveTransmitEvent", "group__lpi2c__slave__driver.html#gga0d99b4dba3841a4e02f7c431a59006c8a976c8c9aa85026224a46cf5ec742eb49", null ],
      [ "kLPI2C_SlaveReceiveEvent", "group__lpi2c__slave__driver.html#gga0d99b4dba3841a4e02f7c431a59006c8ac737ba9e4e62880a6e2d8aac98ae8f18", null ],
      [ "kLPI2C_SlaveTransmitAckEvent", "group__lpi2c__slave__driver.html#gga0d99b4dba3841a4e02f7c431a59006c8a112af4cf8f8a374407d7c784f024b8e0", null ],
      [ "kLPI2C_SlaveRepeatedStartEvent", "group__lpi2c__slave__driver.html#gga0d99b4dba3841a4e02f7c431a59006c8ae0995aac6808b3726b7577c2d283e4c4", null ],
      [ "kLPI2C_SlaveCompletionEvent", "group__lpi2c__slave__driver.html#gga0d99b4dba3841a4e02f7c431a59006c8a06ef7422d9edf9b914864a2d689f042c", null ],
      [ "kLPI2C_SlaveAllEvents", "group__lpi2c__slave__driver.html#gga0d99b4dba3841a4e02f7c431a59006c8aeed0927f4e909cb161b44434b6f01aec", null ]
    ] ],
    [ "LPI2C_SlaveAbortTransfer", "group__lpi2c__slave__driver.html#ga515cda32a1d703a2c0ed7552ab7dfc4d", null ],
    [ "LPI2C_SlaveClearStatusFlags", "group__lpi2c__slave__driver.html#ga3b5306231d96d7fa38ef26d9ca6526b1", null ],
    [ "LPI2C_SlaveCreateHandle", "group__lpi2c__slave__driver.html#ga443cf70e4ba4011e333c0d187230f2fa", null ],
    [ "LPI2C_SlaveDeinit", "group__lpi2c__slave__driver.html#gaa1a5cfe78acec0e1f8dd4af63a0f87f8", null ],
    [ "LPI2C_SlaveDisableInterrupts", "group__lpi2c__slave__driver.html#ga9422103623a9866f350dd03aea984741", null ],
    [ "LPI2C_SlaveEnable", "group__lpi2c__slave__driver.html#gae83a936eb8303218278cd704d8238a08", null ],
    [ "LPI2C_SlaveEnableDMA", "group__lpi2c__slave__driver.html#gaa13d0c04083818cf91af19a6add0e08f", null ],
    [ "LPI2C_SlaveEnableInterrupts", "group__lpi2c__slave__driver.html#gaf5b7a33a341fd95ca77dcb6fe7f1bf3c", null ],
    [ "LPI2C_SlaveGetBusIdleState", "group__lpi2c__slave__driver.html#ga155ee1b5bc8c621b60b349b191c078fc", null ],
    [ "LPI2C_SlaveGetDefaultConfig", "group__lpi2c__slave__driver.html#gadf34085d4557ceb3081fff9fe0e3189a", null ],
    [ "LPI2C_SlaveGetEnabledInterrupts", "group__lpi2c__slave__driver.html#ga3d1fb84d337b8eb5cc19cbeced06c2a1", null ],
    [ "LPI2C_SlaveGetReceivedAddress", "group__lpi2c__slave__driver.html#ga8219a79b748dc59c982c7c3a8470c3a6", null ],
    [ "LPI2C_SlaveGetStatusFlags", "group__lpi2c__slave__driver.html#ga18055724e510f601f35cc00940e9155c", null ],
    [ "LPI2C_SlaveGetTransferCount", "group__lpi2c__slave__driver.html#ga6d19b28a83f2997caf3fcd6927487e98", null ],
    [ "LPI2C_SlaveHandleInterrupt", "group__lpi2c__slave__driver.html#ga2f7c089dea70918c0a08b2caaddd2fe7", null ],
    [ "LPI2C_SlaveInit", "group__lpi2c__slave__driver.html#gae5cc8a03c784a99bb58b69852dfda5a5", null ],
    [ "LPI2C_SlaveReceive", "group__lpi2c__slave__driver.html#ga36dd1b211a7fe488bfc062a1d8e74fc8", null ],
    [ "LPI2C_SlaveReset", "group__lpi2c__slave__driver.html#gaf58f9ebf437d62936c45c201a68fb5d7", null ],
    [ "LPI2C_SlaveSend", "group__lpi2c__slave__driver.html#ga6762c41a46ca9cdc9c749e83f1a9f17d", null ],
    [ "LPI2C_SlaveTransferNonBlocking", "group__lpi2c__slave__driver.html#ga1ba7c9d0c254de8fe8c04091c007edff", null ],
    [ "LPI2C_SlaveTransmitAck", "group__lpi2c__slave__driver.html#ga417e07e45369a955f7fecaa26e13b335", null ]
];