var group__i2c =
[
    [ "i2c_master_config_t", "group__i2c.html#structi2c__master__config__t", [
      [ "baudRate_Bps", "group__i2c.html#aa5df547b4cb95d3c959373cf6fa672b5", null ],
      [ "enableHighDrive", "group__i2c.html#abfd79a5171ca9a694f18e9f6e634186c", null ],
      [ "enableMaster", "group__i2c.html#ab8b96ba3ced8b280ac1f366f6e76a9e7", null ],
      [ "enableStopHold", "group__i2c.html#ac9aaacb54567f1880fcaee7655cbbd79", null ],
      [ "glitchFilterWidth", "group__i2c.html#a0ec674bca5cb7bb8a6c51a44a5fc4314", null ]
    ] ],
    [ "i2c_slave_config_t", "group__i2c.html#structi2c__slave__config__t", [
      [ "addressingMode", "group__i2c.html#a2e946f1dfdd24a753f4c55a6ff3cc2e5", null ],
      [ "enableBaudRateCtl", "group__i2c.html#a788ff5c58438afe177059bf0d3c78d5a", null ],
      [ "enableGeneralCall", "group__i2c.html#aedb9cfa838d8a677d9193d5c92298ea4", null ],
      [ "enableHighDrive", "group__i2c.html#abfd79a5171ca9a694f18e9f6e634186c", null ],
      [ "enableSlave", "group__i2c.html#a9189d8f6438ba99548837da162213c46", null ],
      [ "enableWakeUp", "group__i2c.html#af1f3df39054da492f1da50ca792676af", null ],
      [ "slaveAddress", "group__i2c.html#a67af74c3fc959654c6dc8bcff3a2ea80", null ],
      [ "upperAddress", "group__i2c.html#a959e9269b2e7e83f1c4aebac870bf822", null ]
    ] ],
    [ "i2c_master_transfer_t", "group__i2c.html#structi2c__master__transfer__t", [
      [ "data", "group__i2c.html#a6df23c71c49ca7371f41136934d4fad1", null ],
      [ "dataSize", "group__i2c.html#aec81567ca73e5b0cb790098785e345c5", null ],
      [ "direction", "group__i2c.html#aec93fd70f8f4f4cf2fafcbe0a4df08c2", null ],
      [ "flags", "group__i2c.html#a773b39d480759f67926cb18ae2219281", null ],
      [ "slaveAddress", "group__i2c.html#a7b9ab02d5063e8653f0586395ccd7013", null ],
      [ "subaddress", "group__i2c.html#a6fbfb5e5018422a177a9f3ed7269b127", null ],
      [ "subaddressSize", "group__i2c.html#ab690ec66e8cde484f919799fb1118cd6", null ]
    ] ],
    [ "i2c_master_handle_t", "group__i2c.html#struct__i2c__master__handle", [
      [ "completionCallback", "group__i2c.html#ab886e4f1a8a9cd0953a6dc2b0f33e87c", null ],
      [ "state", "group__i2c.html#a0b57aa10271a66f3dc936bba1d2f3830", null ],
      [ "transfer", "group__i2c.html#a9f792796934731101c55954d82000811", null ],
      [ "transferSize", "group__i2c.html#a10e6d1f095e525fa85ffe957081ed7a7", null ],
      [ "userData", "group__i2c.html#a2e294dd14122c554baa0665072b4ca7a", null ]
    ] ],
    [ "i2c_slave_transfer_t", "group__i2c.html#structi2c__slave__transfer__t", [
      [ "completionStatus", "group__i2c.html#aac6aa92f2aef99293ab2f5ad6f734fad", null ],
      [ "data", "group__i2c.html#a6df23c71c49ca7371f41136934d4fad1", null ],
      [ "dataSize", "group__i2c.html#aec81567ca73e5b0cb790098785e345c5", null ],
      [ "event", "group__i2c.html#ad43dfdc1308f39dd4bff91414c1cce2c", null ],
      [ "transferredCount", "group__i2c.html#a97856cb5d71b7981d4ce9813124a5433", null ]
    ] ],
    [ "i2c_slave_handle_t", "group__i2c.html#struct__i2c__slave__handle", [
      [ "callback", "group__i2c.html#a8630826ced50476e2c1446747c3b2f03", null ],
      [ "eventMask", "group__i2c.html#acf2922a79dce3fb9f7c7fe948de1f5a8", null ],
      [ "isBusy", "group__i2c.html#a099f725f22a344e190121634f53328d8", null ],
      [ "transfer", "group__i2c.html#a8cfa005502ce2f110a54f99672380f5f", null ],
      [ "userData", "group__i2c.html#a2e294dd14122c554baa0665072b4ca7a", null ]
    ] ],
    [ "i2c_master_transfer_callback_t", "group__i2c.html#gafa39d30cd808d79b774361874f227204", null ],
    [ "i2c_slave_transfer_callback_t", "group__i2c.html#ga2583e3d8ebf8d3de410d8b6263238c35", null ],
    [ "_i2c_flags", "group__i2c.html#ga1f1337bbe9d0b184d9dcee31f9ebade2", [
      [ "kI2C_ReceiveNakFlag", "group__i2c.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a4c3c2928e17ddbfbc1c346c6b9a8dccd", null ],
      [ "kI2C_IntPendingFlag", "group__i2c.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a647d0b1d1f9514ad483bef3ea3926c3b", null ],
      [ "kI2C_TransferDirectionFlag", "group__i2c.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a249f698970909f33b1b96139c05bd969", null ],
      [ "kI2C_RangeAddressMatchFlag", "group__i2c.html#gga1f1337bbe9d0b184d9dcee31f9ebade2aac2c3a26d38c01fba1554eddc0c6b8b5", null ],
      [ "kI2C_ArbitrationLostFlag", "group__i2c.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a39fab5ef04e74d00ef4c4574899ab589", null ],
      [ "kI2C_BusBusyFlag", "group__i2c.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a37fb20742a15a63c1bc2551b997cdcff", null ],
      [ "kI2C_AddressMatchFlag", "group__i2c.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a10cd5797b1b8f809192423486a85d5fe", null ],
      [ "kI2C_TransferCompleteFlag", "group__i2c.html#gga1f1337bbe9d0b184d9dcee31f9ebade2adb8f10365dfc2a3e849f05173fa4d83e", null ],
      [ "kI2C_StopDetectFlag", "group__i2c.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a942f41cfdfcd976ab26e77ce95c386ae", null ],
      [ "kI2C_StartDetectFlag", "group__i2c.html#gga1f1337bbe9d0b184d9dcee31f9ebade2a07e611eaff148acca64fae7f1f0e1577", null ]
    ] ],
    [ "_i2c_interrupt_enable", "group__i2c.html#ga87c81dd985dad07dc26cb93125a94ec7", [
      [ "kI2C_GlobalInterruptEnable", "group__i2c.html#gga87c81dd985dad07dc26cb93125a94ec7a5526e27ef6e8317ba928849da890b3b2", null ],
      [ "kI2C_StopDetectInterruptEnable", "group__i2c.html#gga87c81dd985dad07dc26cb93125a94ec7a3d36e9fb0895af1f915abdd66dd7e77c", null ],
      [ "kI2C_StartStopDetectInterruptEnable", "group__i2c.html#gga87c81dd985dad07dc26cb93125a94ec7a3accfbb04bdb6e48e40927efa2269390", null ]
    ] ],
    [ "_i2c_master_transfer_flags", "group__i2c.html#ga87ea07668194cfb46c7c368d2cb42433", [
      [ "kI2C_TransferDefaultFlag", "group__i2c.html#gga87ea07668194cfb46c7c368d2cb42433ae80f7b768b1621e42ac965d3d23de5e2", null ],
      [ "kI2C_TransferNoStartFlag", "group__i2c.html#gga87ea07668194cfb46c7c368d2cb42433a5cb44bf860c0482c0ca0165cf0d31d8a", null ],
      [ "kI2C_TransferRepeatedStartFlag", "group__i2c.html#gga87ea07668194cfb46c7c368d2cb42433aadf112471ef12f194985a093cd9b9721", null ],
      [ "kI2C_TransferNoStopFlag", "group__i2c.html#gga87ea07668194cfb46c7c368d2cb42433afb8aeea71b5b7475e3d3df86220db566", null ]
    ] ],
    [ "_i2c_status", "group__i2c.html#ga7cc91c89125c25a88e463a9e8550b284", [
      [ "kStatus_I2C_Busy", "group__i2c.html#gga7cc91c89125c25a88e463a9e8550b284a49091894b590d7e479605bf113918952", null ],
      [ "kStatus_I2C_Idle", "group__i2c.html#gga7cc91c89125c25a88e463a9e8550b284a628d242f7bc0e3d5949c7f73eafaa508", null ],
      [ "kStatus_I2C_Nak", "group__i2c.html#gga7cc91c89125c25a88e463a9e8550b284a72fd33d0b5263a63766e62f71d16be00", null ],
      [ "kStatus_I2C_ArbitrationLost", "group__i2c.html#gga7cc91c89125c25a88e463a9e8550b284a139b52cc3305ec2c06d0ac94313c221f", null ],
      [ "kStatus_I2C_Timeout", "group__i2c.html#gga7cc91c89125c25a88e463a9e8550b284a81ad7cc198436cabbe91ea55c5288747", null ]
    ] ],
    [ "i2c_direction_t", "group__i2c.html#gab49c827b45635206f06e5737606e4611", [
      [ "kI2C_Write", "group__i2c.html#ggab49c827b45635206f06e5737606e4611a93b476b469c2a4bfed5916b458ae9bb0", null ],
      [ "kI2C_Read", "group__i2c.html#ggab49c827b45635206f06e5737606e4611a3a7bb24dc8d1c1be8925603eeafe9b30", null ]
    ] ],
    [ "i2c_slave_address_mode_t", "group__i2c.html#gac21e18657981bd7861f2ac5ebc5f633b", [
      [ "kI2C_Address7bit", "group__i2c.html#ggac21e18657981bd7861f2ac5ebc5f633ba3e2c7f1f917939d0d7595224e3700dd4", null ],
      [ "kI2C_RangeMatch", "group__i2c.html#ggac21e18657981bd7861f2ac5ebc5f633baa2c312f87691c542c466ff747d21f70a", null ]
    ] ],
    [ "i2c_slave_transfer_event_t", "group__i2c.html#gac53e5c96a2eed1b5a95b7d84be48f4ac", [
      [ "kI2C_SlaveAddressMatchEvent", "group__i2c.html#ggac53e5c96a2eed1b5a95b7d84be48f4acacb1ae174dd6798a6fd79800a9e39a3c6", null ],
      [ "kI2C_SlaveTransmitEvent", "group__i2c.html#ggac53e5c96a2eed1b5a95b7d84be48f4aca2f85039a57379838909876a1d509b7aa", null ],
      [ "kI2C_SlaveReceiveEvent", "group__i2c.html#ggac53e5c96a2eed1b5a95b7d84be48f4acaac8593e808a8137d1b5d3a51640779de", null ],
      [ "kI2C_SlaveTransmitAckEvent", "group__i2c.html#ggac53e5c96a2eed1b5a95b7d84be48f4aca43c045da27fa60e7a0540c743eca4e79", null ],
      [ "kI2C_SlaveRepeatedStartEvent", "group__i2c.html#ggac53e5c96a2eed1b5a95b7d84be48f4aca4c7de9b9d0c71a86ef6bd5cd6a39dad5", null ],
      [ "kI2C_SlaveCompletionEvent", "group__i2c.html#ggac53e5c96a2eed1b5a95b7d84be48f4aca38cca3cd668e73f51b8e574835d419df", null ],
      [ "kI2C_SlaveAllEvents", "group__i2c.html#ggac53e5c96a2eed1b5a95b7d84be48f4aca94b030ebdac378a84961893ae567bfbc", null ]
    ] ],
    [ "I2C_DisableInterrupts", "group__i2c.html#ga9839c1fd49a0f62f42b0adfa74f62853", null ],
    [ "I2C_Enable", "group__i2c.html#gaaaaab1e83cb8c6117046bdb5bcbf9ac6", null ],
    [ "I2C_EnableDMA", "group__i2c.html#gac1c7c015a74aa0e2c8cd7df6dbf7fb71", null ],
    [ "I2C_EnableInterrupts", "group__i2c.html#ga577e094cc4d39b88ec5bbe49bc199c77", null ],
    [ "I2C_GetDataRegAddr", "group__i2c.html#gaf3238d6c3de8e7e8aa7a6c3a8d645769", null ],
    [ "I2C_MasterClearStatusFlags", "group__i2c.html#ga437271ffb955b77df0a5dee9ea80cc63", null ],
    [ "I2C_MasterDeinit", "group__i2c.html#gadcf7122f0a38d4d9da0f052fcb167957", null ],
    [ "I2C_MasterGetDefaultConfig", "group__i2c.html#gad69f2d63ea756dda60749ff6b09f587d", null ],
    [ "I2C_MasterGetStatusFlags", "group__i2c.html#ga721e41295dedc83b424e80e53065e625", null ],
    [ "I2C_MasterInit", "group__i2c.html#ga29f967b3ae8487a36ba2a58deb01ccae", null ],
    [ "I2C_MasterReadBlocking", "group__i2c.html#ga815e953753bbfeea5277b527b16ac23e", null ],
    [ "I2C_MasterRepeatedStart", "group__i2c.html#ga42ff265d25e713326c7d152adf350147", null ],
    [ "I2C_MasterSetBaudRate", "group__i2c.html#gafeab1d5249a8b39c8d9e1a54a85c23f0", null ],
    [ "I2C_MasterStart", "group__i2c.html#ga7664234966e4162e952b6d57efcaa8a6", null ],
    [ "I2C_MasterStop", "group__i2c.html#gaf46a8cc094fc18c6cadea8de71448723", null ],
    [ "I2C_MasterTransferAbort", "group__i2c.html#ga77c9f9c8bc0fe71bbcd9d479f51f8044", null ],
    [ "I2C_MasterTransferBlocking", "group__i2c.html#ga35cae3a5b4aa50ce8db28e3eb703a027", null ],
    [ "I2C_MasterTransferCreateHandle", "group__i2c.html#ga31e3de02b57801c6896e6045c4a31268", null ],
    [ "I2C_MasterTransferGetCount", "group__i2c.html#ga7d720842e68161d2d52d56d119f20665", null ],
    [ "I2C_MasterTransferHandleIRQ", "group__i2c.html#gad091cd1857d2bd8ce64583739b3a35d5", null ],
    [ "I2C_MasterTransferNonBlocking", "group__i2c.html#gac7f76a04b6f6873c52ad176d58901fe9", null ],
    [ "I2C_MasterWriteBlocking", "group__i2c.html#gaba0a9e727e5a141b59b67f10a24dc9e6", null ],
    [ "I2C_SlaveClearStatusFlags", "group__i2c.html#ga545c1a43d8d49c4675de493d45a4063a", null ],
    [ "I2C_SlaveDeinit", "group__i2c.html#gadb50014db29dd75ea2001fb7bc837e77", null ],
    [ "I2C_SlaveGetDefaultConfig", "group__i2c.html#ga7115f80e28b62bbbd3be1a2a918529ba", null ],
    [ "I2C_SlaveGetStatusFlags", "group__i2c.html#gac2794e138d94d9b6a761c074ad0899cd", null ],
    [ "I2C_SlaveInit", "group__i2c.html#gae6e155a5aadb43d527418e2965e39123", null ],
    [ "I2C_SlaveReadBlocking", "group__i2c.html#gaf7409e50ffd9b260744c13863c7a3987", null ],
    [ "I2C_SlaveTransferAbort", "group__i2c.html#ga5ae9f5e6e854d14d33ba3029128bd6f0", null ],
    [ "I2C_SlaveTransferCreateHandle", "group__i2c.html#gac9b90f575d92ff8ad3cc350a5c8ad1b9", null ],
    [ "I2C_SlaveTransferGetCount", "group__i2c.html#gabf38a498bd3527ea0b7cc947ae71e17e", null ],
    [ "I2C_SlaveTransferHandleIRQ", "group__i2c.html#ga097c0b20503381de44cccba311dcf236", null ],
    [ "I2C_SlaveTransferNonBlocking", "group__i2c.html#gaa387d81ea08a9d4b39cfeb3dfec505f7", null ],
    [ "I2C_SlaveWriteBlocking", "group__i2c.html#ga280404c6b1ede542f2c1c20bd382869c", null ]
];