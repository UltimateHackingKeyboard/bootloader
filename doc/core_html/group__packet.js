var group__packet =
[
    [ "command_packet_t", "group__packet.html#structcommand__packet__t", [
      [ "commandTag", "group__packet.html#a516b91715bda900c0f212b4fdb0b047b", null ],
      [ "flags", "group__packet.html#aa2585d779da0ab21273a8d92de9a0ebe", null ],
      [ "parameterCount", "group__packet.html#aee6c95918278d47685463c39e4f2d4d4", null ],
      [ "reserved", "group__packet.html#acb7bc06bed6f6408d719334fc41698c7", null ]
    ] ],
    [ "flash_erase_all_packet_t", "group__packet.html#structflash__erase__all__packet__t", [
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "memoryId", "group__packet.html#a7c1c07009dcc624f8a93d31b5d8484f5", null ]
    ] ],
    [ "flash_erase_region_packet_t", "group__packet.html#structflash__erase__region__packet__t", [
      [ "byteCount", "group__packet.html#aab2b8d46fc5660a5ab68496fe0d7d16b", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "startAddress", "group__packet.html#a3a3fedf4660d77a61d25a4a70a2dfe3d", null ]
    ] ],
    [ "get_property_packet_t", "group__packet.html#structget__property__packet__t", [
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "memoryId", "group__packet.html#a7c1c07009dcc624f8a93d31b5d8484f5", null ],
      [ "propertyTag", "group__packet.html#ada0368dfa6069899ebaa53e039f93a48", null ]
    ] ],
    [ "set_property_packet_t", "group__packet.html#structset__property__packet__t", [
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "propertyTag", "group__packet.html#ada0368dfa6069899ebaa53e039f93a48", null ],
      [ "propertyValue", "group__packet.html#a67fb59c6b9e3ea69f3b6c4d758fba9fe", null ]
    ] ],
    [ "receive_sb_file_packet_t", "group__packet.html#structreceive__sb__file__packet__t", [
      [ "byteCount", "group__packet.html#aab2b8d46fc5660a5ab68496fe0d7d16b", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ]
    ] ],
    [ "write_memory_packet_t", "group__packet.html#structwrite__memory__packet__t", [
      [ "byteCount", "group__packet.html#aab2b8d46fc5660a5ab68496fe0d7d16b", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "startAddress", "group__packet.html#a3a3fedf4660d77a61d25a4a70a2dfe3d", null ]
    ] ],
    [ "read_memory_packet_t", "group__packet.html#structread__memory__packet__t", [
      [ "byteCount", "group__packet.html#aab2b8d46fc5660a5ab68496fe0d7d16b", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "startAddress", "group__packet.html#a3a3fedf4660d77a61d25a4a70a2dfe3d", null ]
    ] ],
    [ "fill_memory_packet_t", "group__packet.html#structfill__memory__packet__t", [
      [ "byteCount", "group__packet.html#aab2b8d46fc5660a5ab68496fe0d7d16b", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "patternWord", "group__packet.html#a15ce01c93a3b2b257a127a72caccc5e7", null ],
      [ "startAddress", "group__packet.html#a3a3fedf4660d77a61d25a4a70a2dfe3d", null ]
    ] ],
    [ "execute_call_packet_t", "group__packet.html#structexecute__call__packet__t", [
      [ "argumentWord", "group__packet.html#aed4f1bcef0f60c8a084b6aea59bf3973", null ],
      [ "callAddress", "group__packet.html#aaf67777c48baca677ed7d87b423d1f03", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "stackpointer", "group__packet.html#a098ef7bcfe72464d77546af8b51763d5", null ]
    ] ],
    [ "flash_security_disable_packet_t", "group__packet.html#structflash__security__disable__packet__t", [
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "keyHigh", "group__packet.html#a50102dbde11ba804276a6ebc70420471", null ],
      [ "keyLow", "group__packet.html#a0d3eed7035b9c3ee84ac13f179cb22bd", null ]
    ] ],
    [ "flash_program_once_packet_t", "group__packet.html#structflash__program__once__packet__t", [
      [ "byteCount", "group__packet.html#aab2b8d46fc5660a5ab68496fe0d7d16b", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "data", "group__packet.html#ad46e24dfc5f73f382b496d79176131e5", null ],
      [ "index", "group__packet.html#aafd95f8c7a99b9189ede7cdf0871ebe8", null ]
    ] ],
    [ "flash_read_once_packet_t", "group__packet.html#structflash__read__once__packet__t", [
      [ "byteCount", "group__packet.html#aab2b8d46fc5660a5ab68496fe0d7d16b", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "index", "group__packet.html#aafd95f8c7a99b9189ede7cdf0871ebe8", null ]
    ] ],
    [ "flash_read_resource_packet_t", "group__packet.html#structflash__read__resource__packet__t", [
      [ "byteCount", "group__packet.html#aab2b8d46fc5660a5ab68496fe0d7d16b", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "option", "group__packet.html#a6ffaa59931174a2a4c4bfa1b1a2d7b1e", null ],
      [ "startAddress", "group__packet.html#a3a3fedf4660d77a61d25a4a70a2dfe3d", null ]
    ] ],
    [ "configure_quadspi_packet_t", "group__packet.html#structconfigure__quadspi__packet__t", [
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "configBlockAddress", "group__packet.html#a2153740048e0c3108036b0f7e89e3a3e", null ],
      [ "flashMemId", "group__packet.html#a25ce6b6b83200841deefcb9454ba5b85", null ]
    ] ],
    [ "reliable_update_packet_t", "group__packet.html#structreliable__update__packet__t", [
      [ "address", "group__packet.html#ac0d31ca829f934cccd89f8054e02773e", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ]
    ] ],
    [ "configure_i2c_packet_t", "group__packet.html#structconfigure__i2c__packet__t", [
      [ "address", "group__packet.html#ac0d31ca829f934cccd89f8054e02773e", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "speed", "group__packet.html#a220859a8b5da0232739a11cbe7f79fc5", null ]
    ] ],
    [ "configure_spi_packet_t", "group__packet.html#structconfigure__spi__packet__t", [
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "direction", "group__packet.html#a2148ffb99828aeaced6a5655502434ac", null ],
      [ "phase", "group__packet.html#a589421fe5ccbd2621e7f17ea192701af", null ],
      [ "polarity", "group__packet.html#a89635a4ddd1c0f43e827bed14908c9d1", null ],
      [ "speedKhz", "group__packet.html#adf6048612c63a339dccec3c045b05912", null ]
    ] ],
    [ "configure_can_packet_t", "group__packet.html#structconfigure__can__packet__t", [
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "rxid", "group__packet.html#a56b38074cabe20ed9d767da2e04e8fed", null ],
      [ "speed", "group__packet.html#a220859a8b5da0232739a11cbe7f79fc5", null ],
      [ "txid", "group__packet.html#ae9541134639576318c3786ab2e730606", null ]
    ] ],
    [ "generic_response_packet_t", "group__packet.html#structgeneric__response__packet__t", [
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "commandTag", "group__packet.html#a831215ac72c0395d0dbc9afdd66bec8a", null ],
      [ "status", "group__packet.html#ade20423e91627f07e610924cb0081623", null ]
    ] ],
    [ "get_property_response_packet_t", "group__packet.html#structget__property__response__packet__t", [
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "propertyValue", "group__packet.html#a77108e3d480171ac0df58b25d9c5f27c", null ],
      [ "status", "group__packet.html#ade20423e91627f07e610924cb0081623", null ]
    ] ],
    [ "read_memory_response_packet_t", "group__packet.html#structread__memory__response__packet__t", [
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "dataByteCount", "group__packet.html#a1594957f2d668c138464205e791c4c36", null ],
      [ "status", "group__packet.html#ade20423e91627f07e610924cb0081623", null ]
    ] ],
    [ "flash_read_once_response_packet_t", "group__packet.html#structflash__read__once__response__packet__t", [
      [ "byteCount", "group__packet.html#aab2b8d46fc5660a5ab68496fe0d7d16b", null ],
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "data", "group__packet.html#ad46e24dfc5f73f382b496d79176131e5", null ],
      [ "status", "group__packet.html#ade20423e91627f07e610924cb0081623", null ]
    ] ],
    [ "flash_read_resource_response_packet_t", "group__packet.html#structflash__read__resource__response__packet__t", [
      [ "commandPacket", "group__packet.html#a97a645f59cb39cc8bd9f9a331a8a5e1c", null ],
      [ "dataByteCount", "group__packet.html#a1594957f2d668c138464205e791c4c36", null ],
      [ "status", "group__packet.html#ade20423e91627f07e610924cb0081623", null ]
    ] ],
    [ "framing_header_t", "group__packet.html#structframing__header__t", [
      [ "packetType", "group__packet.html#a561dfa675631ea8122a078d1243325c4", null ],
      [ "startByte", "group__packet.html#ab4c033cfd9a05c4c5c8688fcb22f88bc", null ]
    ] ],
    [ "framing_sync_packet_t", "group__packet.html#structframing__sync__packet__t", [
      [ "header", "group__packet.html#af0714a84f43a75ea5ed6219503f35df8", null ]
    ] ],
    [ "framing_data_packet_t", "group__packet.html#structframing__data__packet__t", [
      [ "crc16", "group__packet.html#a4438e0df9f58b1861feb3fc659f52534", null ],
      [ "header", "group__packet.html#af0714a84f43a75ea5ed6219503f35df8", null ],
      [ "length", "group__packet.html#a1892eba2086d12ac2b09005aeb09ea3b", null ]
    ] ],
    [ "serial_framing_packet_t", "group__packet.html#structserial__framing__packet__t", [
      [ "data", "group__packet.html#a7a29f09589feb930ce1a84b4de3b7277", null ],
      [ "dataPacket", "group__packet.html#a524a284dbe72b32a1aef8e6c6c757a75", null ]
    ] ],
    [ "serial_data_t", "group__packet.html#structserial__data__t", [
      [ "callbackBuffer", "group__packet.html#a65676b604781a2626dae0b43c714b81a", null ],
      [ "data", "group__packet.html#a92ca89deeb2d4578b7bd7e48c89cec05", null ],
      [ "framingPacket", "group__packet.html#ae9b2f6d232d100f9b461c7df295be3f7", null ],
      [ "isAckAbortNeeded", "group__packet.html#a3496667f52b5f8cd8e34381108268e0a", null ],
      [ "isAckNeeded", "group__packet.html#a830a82b5d823e4db64c763378be77335", null ],
      [ "isBackToBackWrite", "group__packet.html#a394c0a96243ccf6fa1a0e19fe956cd33", null ],
      [ "readOffset", "group__packet.html#ad10650a4450582b790561e4435212b23", null ],
      [ "writeOffset", "group__packet.html#a0b5561925426675ee11f2354f6c642a7", null ]
    ] ],
    [ "ping_response_t", "group__packet.html#structping__response__t", [
      [ "crc16", "group__packet.html#a4438e0df9f58b1861feb3fc659f52534", null ],
      [ "options", "group__packet.html#af86bc430f5b8c737809e0e3baae4ecea", null ],
      [ "version", "group__packet.html#ab5805c535f737e9a32670f5a45b50add", null ]
    ] ],
    [ "call_function_t", "group__packet.html#ga5fa03b6ce5af47fe0d405e97f24a7caf", null ],
    [ "_command_packet_constants", "group__packet.html#gad3df2b7984d0e28379a9a42feb27a873", [
      [ "kMaxPropertyReturnValues", "group__packet.html#ggad3df2b7984d0e28379a9a42feb27a873ad0804f2c4956f6fbb33e072703e109cd", null ],
      [ "kMaxProgramOnceValues", "group__packet.html#ggad3df2b7984d0e28379a9a42feb27a873a93eb60fa3641a4a11cbfb6be2b35772f", null ],
      [ "kCommandTagCount", "group__packet.html#ggad3df2b7984d0e28379a9a42feb27a873a565f0323e8b6751f6ca47a6d128f876b", null ]
    ] ],
    [ "_command_packet_flags", "group__packet.html#gaf117778d1938807c8e0fffeb39c672df", null ],
    [ "_command_tags", "group__packet.html#gaefc521e8d8a1bb32e9278d8f92f1115e", [
      [ "kCommandTag_ConfigureSpi", "group__packet.html#ggaefc521e8d8a1bb32e9278d8f92f1115eafc06db4bc9e0f280693de6fa621f42c1", null ],
      [ "kCommandTag_ConfigureCan", "group__packet.html#ggaefc521e8d8a1bb32e9278d8f92f1115eaff91871aba6809647dde98f1ecd6463a", null ],
      [ "kFirstCommandTag", "group__packet.html#ggaefc521e8d8a1bb32e9278d8f92f1115ea8d2b30d9f5604f9de6484a47664d8e25", null ],
      [ "kLastCommandTag", "group__packet.html#ggaefc521e8d8a1bb32e9278d8f92f1115ead37204f9baf3f14abcefc9d8d82d88ea", null ],
      [ "kResponseCommandHighNibbleMask", "group__packet.html#ggaefc521e8d8a1bb32e9278d8f92f1115ead61de9bf3e638999f380e8bf4b3f3d67", null ]
    ] ],
    [ "_flash_mem_id", "group__packet.html#ga3b7b39313fa770abac072b813fbe2e60", null ],
    [ "_framing_packet_constants", "group__packet.html#ga62b42db1f8bbcdcd1a9e28220ee4627e", null ],
    [ "_serial_packet_constants", "group__packet.html#gac4680247a99210ad5bb3e2dfb634dfd3", null ],
    [ "_serial_packet_mode", "group__packet.html#ga2a8f13fe838021db8eeaf217ff17a9db", null ],
    [ "_serial_protocol_version_constants", "group__packet.html#ga012b8bb615153c433c06843e404084b0", null ],
    [ "_timing_constants", "group__packet.html#ga2c66f7e3d2dacb6bf4f217f66e60ed00", [
      [ "kDefaultByteReadTimeoutMs", "group__packet.html#gga2c66f7e3d2dacb6bf4f217f66e60ed00ad24537294d9e3209afa42a1ee7081f4d", null ],
      [ "kCallbackBufferSize", "group__packet.html#gga2c66f7e3d2dacb6bf4f217f66e60ed00a54286149a8cc228b9668daf91c21dfda", null ]
    ] ],
    [ "calculate_framing_crc16", "group__packet.html#ga218748fd1c0987305a058ad4f24bbe95", null ],
    [ "read_crc16", "group__packet.html#ga78781b6dc665ce57e4ff3f5b1c9fc8f0", null ],
    [ "read_data", "group__packet.html#gabeb657f00ab168f281a435ede2232e67", null ],
    [ "read_data_packet", "group__packet.html#gab27002b66fbf490c4975ae374608303d", null ],
    [ "read_header", "group__packet.html#gaf00c2f837635865d4d1059aeca00d6f2", null ],
    [ "read_length", "group__packet.html#ga9c52fd15222fe89c53e0f16809e99051", null ],
    [ "read_start_byte", "group__packet.html#ga30d2176721f80537c2a242c1886243d3", null ],
    [ "send_deferred_ack", "group__packet.html#ga4117d35f00b344603bb673f75832d9a0", null ],
    [ "serial_packet_abort", "group__packet.html#ga1a60f41326f758000304976fd18d65a2", null ],
    [ "serial_packet_finalize", "group__packet.html#ga68e805a1882eb220f1ddd9a08c26030b", null ],
    [ "serial_packet_get_max_packet_size", "group__packet.html#ga598a287b57672291406cff9c728e03f9", null ],
    [ "serial_packet_init", "group__packet.html#ga3707af76120e3f97302536c0615f7add", null ],
    [ "serial_packet_queue_byte", "group__packet.html#ga88407143978559f83d7115b86dc876be", null ],
    [ "serial_packet_read", "group__packet.html#gaec8900ed4ea5a3c981d66dab38516643", null ],
    [ "serial_packet_send_sync", "group__packet.html#gab0420ede400b98b1c21a7a7713b57633", null ],
    [ "serial_packet_write", "group__packet.html#ga7bcf4e62f6cbc2ab39c1666c1d5e752a", null ],
    [ "serial_send_ping_response", "group__packet.html#gabb5327f7eac946ecd5bf73b12565a502", null ],
    [ "wait_for_ack_packet", "group__packet.html#ga34f308d460efca1f58e045f8ee3f09de", null ],
    [ "write_data", "group__packet.html#ga133c8f47194b9aec1935136a09ff0a69", null ],
    [ "g_serialContext", "group__packet.html#ga625bcffc6e8f34be003eac627b5414dc", null ],
    [ "k_PingResponse", "group__packet.html#gadd274c1ccd09e20f83594c95076d1218", null ]
];