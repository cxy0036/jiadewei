
//const unsigned char g_abMaxxDSPCommands[] =
 unsigned char code g_abMaxxDSPCommands[] =	
{
    0x00, 0xa5, 0x00, /* Command DETECT                             */
    0x00, 0xa5, 0x00, /* Command DETECT                             */

    /* System Configuration Begin */
    0x00, 0xc3, 0x00, /* Command SAMPLE, Value = 48 kHz             */
    0x00, 0xa4, 0x11, /* Command ANALOG_SETTING                     */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x10, 0x1d, 0x3f, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x6a, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x7f, 0xff, 0xff, /*                                            */
    0x00, 0x03, 0x66, /*                                            */
    0x00, 0x03, 0x56, /*                                            */
    0x00, 0x03, 0xde, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x43, 0x2c, 0xe3, /*                                            */
    0x00, 0xc8, 0x00, /* Command UPD_ANALOG                         */
    0xbf, 0xc4, 0xd5, /* Command DIG_IO_CONFIG, Value = 0000d5      */
    0xff, 0xab, 0xfb, 
    0x24, 0x10, 0x09, /*                                            */
    0xff, 0xab, 0xfa, 
    0x08, 0x00, 0x09, /*                                            */
    0xff, 0xab, 0xfa, 
    0x00, 0x00, 0x09, /*                                            */
    0xff, 0xab, 0xfb, 
    0xa4, 0x18, 0x29, /*                                            */
    0xff, 0xad, 0x84, 
    0x00, 0x00, 0x18, /*                                            */
    0xff, 0xad, 0x85, 
    0x00, 0x1f, 0xff, /*                                            */
    0xff, 0xad, 0x81, 
    0x00, 0x12, 0x12, /*                                            */
    0xff, 0xad, 0x82, 
    0x00, 0x14, 0x14, /*                                            */
    0xff, 0xad, 0x83, 
    0x00, 0x00, 0x99, /*                                            */
    0xff, 0xad, 0x80, 
    0x00, 0x54, 0x54, /*                                            */
    0xff, 0xad, 0x87, 
    0x00, 0x54, 0x54, /*                                            */
    0xff, 0xad, 0x86, 
    0x00, 0x00, 0x00, /*                                            */
    0xff, 0xad, 0x86, 
    0x00, 0x00, 0x01, /*                                            */
    0xff, 0xad, 0x86, 
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0xc2, 0x00, /* Command SPEAKER, Value = 2.0               */
    /* System Configuration End */

    /* Algorithms Configuration Begin */
    0x00, 0xc9, 0x79, /* Command BALANCE, Value = 0                 */
    0x00, 0xdf, 0x14, /* Command LEVELER_TARGET, Value = -4.0       */
    0x00, 0xdb, 0x3c, /* Command LEVELER_RANGE, Value = -12.0       */
    0x00, 0xdb, 0x3c, /* Command LEVELER_RANGE, Value = -12.0       */
    0x00, 0xc7, 0x00, /* Command MUTE, Value = Out                  */
    0x00, 0xe0, 0x0a, /* Command MUTE, Value = 10                   */
    0x00, 0xd5, 0x60, /* Command MAXX_BASS_FREQUENCY, Value = 79.8  */
    0x00, 0xe3, 0x43, /* Command MAXX_BASS_HP_FREQUENCY, Value = 35 */
    0x00, 0xcf, 0x04, /* Command Internal                           */
    0x00, 0xe1, 0x70, /* Command MAXX_BASS_NG_THRESHOLD, Value = -100 */
    0x00, 0xcb, 0x00, /* Command MAXX_BASS_ORIGINAL_BASS, Value = Off */
    0x00, 0xe2, 0x2f, /* Command MAXX_BASS_NG_GAP, Value = -47      */
    0x00, 0xd9, 0x5b, /* Command MAXX_TREBLE_FREQUENCY, Value = 6998.8 */
    0x00, 0xe5, 0x2f, /* Command MAXX_TREBLE_NG_GAP, Value = -47    */
    0x00, 0xe4, 0x70, /* Command MAXX_TREBLE_NG_THRESHOLD, Value = -100 */
    0x00, 0xd7, 0x30, /* Command SUB_FREQ, Value = 20.0             */
    0x01, 0xd0, 0x91, /* Command MAXX_VOLUME_SLIDER                 */
    0x00, 0xc6, 0x01, /* Command LEVELER_ON_OFF                     */
    0x00, 0xdd, 0x01, /* Command HARD_KNEE                          */
    0x00, 0xd4, 0x15, /* Command VOLUME_DYN_RANGE                   */
    0x00, 0xda, 0x06, /* Command VOLUME_LOW_GAIN                    */
    0x00, 0xdc, 0x10, /* Command VOLUME_GATE                        */
    0x00, 0xa1, 0x05, /* Command SET_PEQ                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x01, /*                                            */
    0x00, 0x00, 0x15, /*                                            */
    0x00, 0x00, 0x17, /*                                            */
    0x00, 0x00, 0x1f, /*                                            */
    0x00, 0xd8, 0x00, /* Command UPD_PEQ                            */
    0x00, 0xa1, 0x05, /* Command SET_PEQ                            */
    0x00, 0x00, 0x01, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x12, /*                                            */
    0x00, 0x00, 0x68, /*                                            */
    0x00, 0x00, 0x53, /*                                            */
    0x00, 0xd8, 0x00, /* Command UPD_PEQ                            */
    0x00, 0xa1, 0x05, /* Command SET_PEQ                            */
    0x00, 0x00, 0x02, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x1f, /*                                            */
    0x00, 0x00, 0x7f, /*                                            */
    0x00, 0x00, 0x21, /*                                            */
    0x00, 0xd8, 0x00, /* Command UPD_PEQ                            */
    0x00, 0xa1, 0x05, /* Command SET_PEQ                            */
    0x00, 0x00, 0x03, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x26, /*                                            */
    0x00, 0x00, 0x1d, /*                                            */
    0x00, 0x00, 0x48, /*                                            */
    0x00, 0xd8, 0x00, /* Command UPD_PEQ                            */
    0x00, 0xa1, 0x05, /* Command SET_PEQ                            */
    0x00, 0x00, 0x04, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x35, /*                                            */
    0x00, 0x00, 0x2b, /*                                            */
    0x00, 0x00, 0x48, /*                                            */
    0x00, 0xd8, 0x00, /* Command UPD_PEQ                            */
    0x00, 0xa1, 0x05, /* Command SET_PEQ                            */
    0x00, 0x00, 0x05, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x43, /*                                            */
    0x00, 0x00, 0x33, /*                                            */
    0x00, 0x00, 0x44, /*                                            */
    0x00, 0xd8, 0x00, /* Command UPD_PEQ                            */
    0x00, 0xa1, 0x05, /* Command SET_PEQ                            */
    0x00, 0x00, 0x06, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x3c, /*                                            */
    0x00, 0x00, 0x3a, /*                                            */
    0x00, 0x00, 0x3f, /*                                            */
    0x00, 0xd8, 0x00, /* Command UPD_PEQ                            */
    0x00, 0xa1, 0x05, /* Command SET_PEQ                            */
    0x00, 0x00, 0x07, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x63, /*                                            */
    0x00, 0x00, 0x0d, /*                                            */
    0x00, 0x00, 0x3a, /*                                            */
    0x00, 0xd8, 0x00, /* Command UPD_PEQ                            */
    0x00, 0xa1, 0x05, /* Command SET_PEQ                            */
    0x00, 0x00, 0x08, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x73, /*                                            */
    0x00, 0x00, 0x28, /*                                            */
    0x00, 0x00, 0x54, /*                                            */
    0x00, 0xd8, 0x00, /* Command UPD_PEQ                            */
    0x00, 0xa1, 0x05, /* Command SET_PEQ                            */
    0x00, 0x00, 0x09, /*                                            */
    0x00, 0x00, 0x00, /*                                            */
    0x00, 0x00, 0x79, /*                                            */
    0x00, 0x00, 0x02, /*                                            */
    0x00, 0x00, 0x66, /*                                            */
    0x00, 0xd8, 0x00, /* Command UPD_PEQ                            */
    0x00, 0xcf, 0x01, /*                                            */
    0x00, 0xd1, 0x00, /*                                            */
    0x00, 0xd1, 0x09, /*                                            */
    0x00, 0xd1, 0x12, /*                                            */
    0x00, 0xd1, 0x1b, /*                                            */
    0x00, 0xd1, 0x24, /*                                            */
    0x00, 0xd1, 0x2d, /*                                            */
    0x00, 0xd1, 0x36, /*                                            */
    0x00, 0xd1, 0x3f, /*                                            */
    0x00, 0xd1, 0x48, /*                                            */
    0x00, 0xd1, 0x4c, /*                                            */
    0x00, 0xd1, 0x16, /* Command MAXX_BASS_INTENSITY                */
    0x00, 0xcf, 0x04, /* Command Internal                           */
    0x00, 0xd2, 0x48, /* Command MAXX_TREBLE_INTENSITY              */
    0x00, 0xcf, 0x04, /* Command Internal                           */
    0x00, 0xcf, 0x04, /* Command Internal                           */
    0x00, 0xe8, 0x56, 
    0x00, 0xe9, 0x55, 
    0x00, 0xcf, 0x04, /* Command Internal                           */

    /* Patch Begin */
    0xff, 0xab, 0xf3, /*                                            */
    0x00, 0x00, 0xc1, /*                                            */
    0xff, 0xab, 0xf4, /*                                            */
    0x00, 0x00, 0x01, /*                                            */
    0xff, 0xab, 0xf5, /*                                            */
    0x30, 0x1a, 0x48, /*                                            */
    0xff, 0xab, 0xf6, /*                                            */
    0x20, 0xee, 0x7d, /*                                            */
    0xff, 0xab, 0xf7, /*                                            */
    0x02, 0x90, 0x78, /*                                            */
    0xff, 0xab, 0xf4, /*                                            */
    0x00, 0x00, 0x02, /*                                            */
    0xff, 0xab, 0xf5, /*                                            */
    0x10, 0x1a, 0x4a, /*                                            */
    0xff, 0xab, 0xf6, /*                                            */
    0x21, 0xe6, 0x00, /*                                            */
    0x06, 0xaa, 0x06, /*                                            */
    0x00, 0xa2, 0x7b, /*                                            */
    0x61, 0xf4, 0x00, /*                                            */
    0x00, 0x00, 0x90, /*                                            */
    0x61, 0x70, 0x00, /*                                            */
    0x00, 0x02, 0x47, /*                                            */
    0x3c, 0x0a, 0x00, /*                                            */
    0x38, 0x0a, 0x00, /*                                            */
    0x64, 0xf4, 0x00, /*                                            */
    0x00, 0x01, 0x34, /*                                            */
    0x60, 0xf4, 0x00, /*                                            */
    0x00, 0x01, 0xda, /*                                            */
    0x05, 0xf4, 0x20, /*                                            */
    0xff, 0xff, 0xff, /*                                            */
    0x04, 0x64, 0xa0, /*                                            */
    0x20, 0x4c, 0x00, /*                                            */
    0x20, 0x48, 0x00, /*                                            */
    0x44, 0xb8, 0x00, /*                                            */
    0x0c, 0xc4, 0xa0, /*                                            */
    0x00, 0x00, 0x16, /*                                            */
    0x57, 0xf4, 0x00, /*                                            */
    0x7f, 0xf7, 0x05, /*                                            */
    0x5f, 0x5c, 0x00, /*                                            */
    0x5f, 0x58, 0x00, /*                                            */
    0x57, 0xf4, 0x00, /*                                            */
    0x7f, 0xff, 0x38, /*                                            */
    0x5f, 0x5c, 0x00, /*                                            */
    0x5f, 0x58, 0x00, /*                                            */
    0x20, 0x5c, 0x00, /*                                            */
    0x20, 0x58, 0x00, /*                                            */
    0x57, 0xf4, 0x00, /*                                            */
    0x7f, 0xff, 0xbc, /*                                            */
    0x5f, 0x5c, 0x00, /*                                            */
    0x5f, 0x58, 0x00, /*                                            */
    0x57, 0xf4, 0x00, /*                                            */
    0x7f, 0xc7, 0x29, /*                                            */
    0x5f, 0x5c, 0x00, /*                                            */
    0x5f, 0x58, 0x00, /*                                            */
    0x0a, 0xf0, 0x80, /*                                            */
    0x00, 0x00, 0x78, /*                                            */
    0x57, 0xf4, 0x00, /*                                            */
    0x7f, 0xf6, 0x3a, /*                                            */
    0x5f, 0x5c, 0x00, /*                                            */
    0x5f, 0x58, 0x00, /*                                            */
    0x57, 0xf4, 0x00, /*                                            */
    0x7f, 0xff, 0x27, /*                                            */
    0x5f, 0x5c, 0x00, /*                                            */
    0x5f, 0x58, 0x00, /*                                            */
    0x20, 0x5c, 0x00, /*                                            */
    0x20, 0x58, 0x00, /*                                            */
    0x57, 0xf4, 0x00, /*                                            */
    0x7f, 0xff, 0xb6, /*                                            */
    0x5f, 0x5c, 0x00, /*                                            */
    0x5f, 0x58, 0x00, /*                                            */
    0x57, 0xf4, 0x00, /*                                            */
    0x7f, 0xc2, 0x23, /*                                            */
    0x5f, 0x5c, 0x00, /*                                            */
    0x5f, 0x58, 0x00, /*                                            */
    0x54, 0xf0, 0x00, /*                                            */
    0xff, 0xff, 0xf1, /*                                            */
    0x0c, 0x1e, 0xe2, /*                                            */
    0x01, 0x40, 0xc6, /*                                            */
    0x00, 0x00, 0x07, /*                                            */
    0x01, 0x40, 0xc5, /*                                            */
    0x00, 0x00, 0x01, /*                                            */
    0x0a, 0xf0, 0xa2, /*                                            */
    0x00, 0x00, 0x89, /*                                            */
    0x61, 0xf4, 0x00, /*                                            */
    0x00, 0xcd, 0xac, /*                                            */
    0x61, 0x70, 0x00, /*                                            */
    0x00, 0x02, 0x14, /*                                            */
    0x61, 0xf4, 0x00, /*                                            */
    0x00, 0xc8, 0x32, /*                                            */
    0x61, 0x70, 0x00, /*                                            */
    0x00, 0x01, 0xff, /*                                            */
    0x60, 0xf4, 0x00, /*                                            */
    0x00, 0x00, 0x98, /*                                            */
    0x60, 0x70, 0x00, /*                                            */
    0x00, 0x01, 0xf8, /*                                            */
    0x0b, 0xf0, 0x80, /*                                            */
    0x00, 0x00, 0x98, /*                                            */
    0x00, 0x00, 0x0c, /*                                            */
    0x0b, 0xf0, 0x80, /*                                            */
    0x00, 0xd3, 0x68, /*                                            */
    0x46, 0xf4, 0x00, /*                                            */
    0x4d, 0xf8, 0xf0, /*                                            */
    0x74, 0xf4, 0x00, /*                                            */
    0x00, 0x00, 0x1e, /*                                            */
    0x4e, 0x6c, 0x00, /*                                            */
    0x00, 0x00, 0x0c, /*                                            */
    0x55, 0xbe, 0x00, /*                                            */
    0x01, 0x40, 0xce, /*                                            */
    0xff, 0xff, 0x3f, /*                                            */
    0x30, 0xff, 0x00, /*                                            */
    0x04, 0xcd, 0xcd, /*                                            */
    0x20, 0x00, 0x1b, /*                                            */
    0x22, 0x09, 0x00, /*                                            */
    0x00, 0x00, 0x0b, /*                                            */
    0x0d, 0x10, 0x4a, /*                                            */
    0x00, 0x00, 0x0a, /*                                            */
    0x0a, 0x9d, 0xa1, /*                                            */
    0x00, 0x00, 0x9f, /*                                            */
    0x22, 0x09, 0x00, /*                                            */
    0x00, 0x00, 0x0b, /*                                            */
    0x0d, 0x10, 0x4a, /*                                            */
    0x00, 0x00, 0x04, /*                                            */
    0x0a, 0x9d, 0x81, /*                                            */
    0x00, 0x00, 0xa5, /*                                            */
    0x08, 0x45, 0x1a, /*                                            */
    0x56, 0xf4, 0x00, /*                                            */
    0x00, 0x03, 0xff, /*                                            */
    0x20, 0x00, 0x62, /*                                            */
    0x08, 0xcc, 0x1a, /*                                            */
    0x07, 0xf0, 0x2d, /*                                            */
    0x00, 0x00, 0x3e, /*                                            */
    0x57, 0xf0, 0x00, /*                                            */
    0x00, 0x02, 0xac, /*                                            */
    0x45, 0xf4, 0x00, /*                                            */
    0x00, 0x00, 0x02, /*                                            */
    0x45, 0xf4, 0x6a, /*                                            */
    0xff, 0x0f, 0xff, /*                                            */
    0x20, 0x00, 0x6e, /*                                            */
    0x55, 0x70, 0x00, /*                                            */
    0x00, 0x02, 0xac, /*                                            */
    0x00, 0x00, 0x0c, /*                                            */
    /* Patch End */

    0x00, 0xac, 0x00, /* Command COMLET_SETTING                     */
    0x00, 0x85, 0x00, /* Command Internal                           */
};
