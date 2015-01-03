<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>ai.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/ai/</path>
    <filename>ai_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>aiInit</name>
      <anchorfile>ai_8h.html</anchorfile>
      <anchor>aaea50d98f0f573a61570b4dfb06f6902</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ai</name>
      <anchorfile>ai_8h.html</anchorfile>
      <anchor>ac15964a73c0279f89af4fa0e522ee587</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>controller.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/control/</path>
    <filename>controller_8h</filename>
    <includes id="pid_8h" name="pid.h" local="yes" imported="no">control/pid.h</includes>
    <class kind="struct">Controller</class>
    <member kind="typedef">
      <type>struct Controller</type>
      <name>Controller</name>
      <anchorfile>controller_8h.html</anchorfile>
      <anchor>a7a6f6d9c95caece2efa460a38c6c496a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ControllerState</name>
      <anchorfile>controller_8h.html</anchorfile>
      <anchor>ac38090c7c72c6db6eacb377d6224ad36</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>CS_PositionControl</name>
      <anchorfile>controller_8h.html</anchorfile>
      <anchor>ac38090c7c72c6db6eacb377d6224ad36a466835c570a4787a88a37432ecd27e73</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>CS_SpeedControl</name>
      <anchorfile>controller_8h.html</anchorfile>
      <anchor>ac38090c7c72c6db6eacb377d6224ad36a64848935f55a66d03d23f0e6cc4d8e52</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>CS_Braking</name>
      <anchorfile>controller_8h.html</anchorfile>
      <anchor>ac38090c7c72c6db6eacb377d6224ad36ab685145bad54ee71f70dd4c5f31d98e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <type>@</type>
      <name>CS_Calibration</name>
      <anchorfile>controller_8h.html</anchorfile>
      <anchor>ac38090c7c72c6db6eacb377d6224ad36a1284faf89227583032ab2431efed3079</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>controllerUpdate</name>
      <anchorfile>controller_8h.html</anchorfile>
      <anchor>ac3665e1dae8d899f63009c860f9ffbc0</anchor>
      <arglist>(float error_length, float error_angle)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>controllerAngleOptimization</name>
      <anchorfile>controller_8h.html</anchorfile>
      <anchor>ae1f82206456a705840dc36a984de71d4</anchor>
      <arglist>(float relative_x, float relative_y, float final_angle, float current_error_angle)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>controllerChangeState</name>
      <anchorfile>controller_8h.html</anchorfile>
      <anchor>a29f9c103759a3ffd94c48779a9f4fa41</anchor>
      <arglist>(ControllerState state)</arglist>
    </member>
    <member kind="variable">
      <type>Controller</type>
      <name>controller</name>
      <anchorfile>controller_8h.html</anchorfile>
      <anchor>a872eb72dc091dfc922f3461989909363</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>encoders.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/control/</path>
    <filename>encoders_8h</filename>
    <class kind="struct">Encoder</class>
    <member kind="typedef">
      <type>struct Encoder</type>
      <name>Encoder</name>
      <anchorfile>encoders_8h.html</anchorfile>
      <anchor>aefe90a9b9c3700044de5961dd53c9224</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>encodersInit</name>
      <anchorfile>encoders_8h.html</anchorfile>
      <anchor>a04f27e1b81746b2868feecb5760055fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>encodersFetch</name>
      <anchorfile>encoders_8h.html</anchorfile>
      <anchor>ac5926bf80797d9511f68776ace90df14</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>encodersGetLengthVariation</name>
      <anchorfile>encoders_8h.html</anchorfile>
      <anchor>aa4ebbfb1be8bce7b29077563dde83a24</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>encodersGetAngleVariation</name>
      <anchorfile>encoders_8h.html</anchorfile>
      <anchor>aaea20ebdd4360ceab475f3623b781776</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>Encoder</type>
      <name>encoder_right</name>
      <anchorfile>encoders_8h.html</anchorfile>
      <anchor>a07f80f69ac3249e4a9231146dc7cacd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Encoder</type>
      <name>encoder_left</name>
      <anchorfile>encoders_8h.html</anchorfile>
      <anchor>add1f1b5280a5862217bbc5d78bb819ff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>motors.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/control/</path>
    <filename>motors_8h</filename>
    <includes id="bits_8h" name="bits.h" local="yes" imported="no">tools/bits.h</includes>
    <member kind="function">
      <type>void</type>
      <name>motorsInit</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a16775dbdcf6f9b0714fdfbdaac209862</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>motorsBrake</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a30b5bfae77991cdca041bdc92980ec2c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>motorsUnbrake</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a26dfdf61af135d41c8f0fe98c7cad0b6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>motorsApplyOrder</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a65599abe25365b320c0f6181759a2656</anchor>
      <arglist>(float order_lenght, float order_angle)</arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>motors_dir_r</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a9b0ae801dc4aece8ed5c5d5bfd5442fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>motors_dir_l</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a58cc7c3a18b2320469a87bc7e8799712</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>motors_brake_r</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>af0f5b12434b4438057f30d55e82a6b9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>motors_brake_l</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>adaae7b7d154a3670d0da0e8dbb24af5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>regPtr</type>
      <name>motors_pwm_r</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a2959a1708cc99a67c5fb7518f79bb514</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>regPtr</type>
      <name>motors_pwm_l</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a1d7b2c4aeedd59389e7f98740262edbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>motors_dir_l_tris</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>ad4af5506805addcce1a076f62e0b331d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>motors_dir_r_tris</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a662d710f02b3a845acfd8843b401922a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>motors_brake_l_tris</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a5dfdcd931d5da66e1b8d159b2e5a355b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>motors_brake_r_tris</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a9f534f26fd5c5ff047204aaf0ca781bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>motors_pwm_l_tris</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>ad16d1b1959fe99437d3c7b3b000a11c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>motors_pwm_r_tris</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>ab121cba7e9f64206dfdb4fe28ede9694</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>motors_PTP</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a5864033c0bd1f6147880f71573835ce9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>pwm_max</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>aef3fdbd7cb9921a33d258bded6f3a4b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>pwm_min</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a3ebea0ac266a2e5b18d00823947eee47</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>coef_angle</name>
      <anchorfile>motors_8h.html</anchorfile>
      <anchor>a512cd8960fe2d9f7cf07c0225e2968f0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pid.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/control/</path>
    <filename>pid_8h</filename>
    <class kind="struct">PID</class>
    <member kind="typedef">
      <type>struct PID</type>
      <name>PID</name>
      <anchorfile>pid_8h.html</anchorfile>
      <anchor>af51bc4a750292b52533cbf015ded103c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>pidGetOrder</name>
      <anchorfile>pid_8h.html</anchorfile>
      <anchor>afaea1b9ce1ce7a26abb22a435d80f9dd</anchor>
      <arglist>(PID *pid, float error)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>leds.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/debug/</path>
    <filename>leds_8h</filename>
    <includes id="bits_8h" name="bits.h" local="yes" imported="no">tools/bits.h</includes>
    <member kind="function">
      <type>void</type>
      <name>ledsInit</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>aadcaa5aaa722b9e5699f50c6d9ca7bfe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ledSet</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>ac0224bc9f355ba6b6049d7d1c6f2b21a</anchor>
      <arglist>(uint8_t led, bool state)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ledToggle</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a5569d5400961537b4827e980e7428201</anchor>
      <arglist>(uint8_t led)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ledSetAll</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a2c23dda80fe368fe1f8dff244e06f35f</anchor>
      <arglist>(uint8_t value)</arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led0</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>ab91cf913e5d0206140b6f4ae7cffe5db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led1</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a7730a723bfe5853997b1a4dba36d16e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led2</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a918c2bd58b8c69b98a2306b51a98ef1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led3</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a61d7d4587eda6783f85b12b3427ab027</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led4</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a3ac9ed69f7213334d726371120f6ead8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led5</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a3c5cbb937c09a449e8fa0ad097f3204a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led6</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a912ec86251184771b36b5112e9e2a1e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led7</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>ac500e516b94564823bff9f0662063373</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led0_tris</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a583e07fffd2f8940d28c7d249c6a8518</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led1_tris</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>ae99f2a37c9b88d105e1f70079c24b05e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led2_tris</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a5a06fdc383a23b2bfc4cad3383ac21d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led3_tris</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a9ff41bb2a196adc36a0b39d74cf6a132</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led4_tris</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>acb2b51d1569df53a4c0553c0604c2393</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led5_tris</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a3ba47958c35967f9ccc387beee24c4a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led6_tris</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a1f3cb56ddf0d6d64dc5f4439e0322c49</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bitPtr</type>
      <name>led7_tris</name>
      <anchorfile>leds_8h.html</anchorfile>
      <anchor>a3c9e21502ec07eb8d7801885fa812acb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>log.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/debug/</path>
    <filename>log_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>logInit</name>
      <anchorfile>log_8h.html</anchorfile>
      <anchor>a922fe26598492a0117d8b89b417e7df5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>logClose</name>
      <anchorfile>log_8h.html</anchorfile>
      <anchor>a4ae2f30247026f94d61cf36e53c905ba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>logString</name>
      <anchorfile>log_8h.html</anchorfile>
      <anchor>a1c048c635792c40e59c0dadfeeb93429</anchor>
      <arglist>(const char *string)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>logStringFormatted</name>
      <anchorfile>log_8h.html</anchorfile>
      <anchor>af98bbbe247b6eb2e2ce493b950695bd7</anchor>
      <arglist>(const char *fmt,...)</arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>log_final_baud</name>
      <anchorfile>log_8h.html</anchorfile>
      <anchor>af1a817aa278ae365053c28dc6b7ab921</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>adc.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/io/</path>
    <filename>adc_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>adcInit</name>
      <anchorfile>adc_8h.html</anchorfile>
      <anchor>ae4f365b3739f2a3b62b862af84937609</anchor>
      <arglist>(uint8_t *channels, size_t channels_num)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>adcPoll</name>
      <anchorfile>adc_8h.html</anchorfile>
      <anchor>a3a1308b05aa679adb9da243986b9365d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>uint16_t</type>
      <name>adcGetChannel</name>
      <anchorfile>adc_8h.html</anchorfile>
      <anchor>a2d0d5a65f5512e8066b0c38e9c76897b</anchor>
      <arglist>(uint8_t channel)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>config_flash.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/io/</path>
    <filename>config__flash_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>configInit</name>
      <anchorfile>config__flash_8h.html</anchorfile>
      <anchor>acc4dab5675c12593144b7dd4df359961</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>configLoadFromFlash</name>
      <anchorfile>config__flash_8h.html</anchorfile>
      <anchor>a597b3b2c7d486553fda7b762dd982417</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>configSaveToFlash</name>
      <anchorfile>config__flash_8h.html</anchorfile>
      <anchor>aa8f7789c929c419a34c9cd54a99d7215</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>configuration</name>
      <anchorfile>config__flash_8h.html</anchorfile>
      <anchor>a882c74f254eb21b9882195a28b0de010</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>dxl_hal.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/io/</path>
    <filename>dxl__hal_8h</filename>
    <member kind="function">
      <type>int</type>
      <name>dxl_hal_open</name>
      <anchorfile>dxl__hal_8h.html</anchorfile>
      <anchor>a98248584e4e6a9638496d19d947168e4</anchor>
      <arglist>(int devIndex, float baudrate)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_hal_close</name>
      <anchorfile>dxl__hal_8h.html</anchorfile>
      <anchor>a285b8abbb0836d0fd2038931efa552db</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_hal_clear</name>
      <anchorfile>dxl__hal_8h.html</anchorfile>
      <anchor>a2888c616f3aef83df34237af25843a77</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_hal_tx</name>
      <anchorfile>dxl__hal_8h.html</anchorfile>
      <anchor>aafc59ee5f350fefcfa23fa2210681487</anchor>
      <arglist>(unsigned char *pPacket, int numPacket)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_hal_rx</name>
      <anchorfile>dxl__hal_8h.html</anchorfile>
      <anchor>adf8a6d157923961a0e4da2a28c07de45</anchor>
      <arglist>(unsigned char *pPacket, int numPacket)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_hal_set_timeout</name>
      <anchorfile>dxl__hal_8h.html</anchorfile>
      <anchor>a1af55b50fcef1780fed3e97ae72a3188</anchor>
      <arglist>(int NumRcvByte)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_hal_timeout</name>
      <anchorfile>dxl__hal_8h.html</anchorfile>
      <anchor>ab1f974f2c52512512a2c077bab72b339</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>dynamixel.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/io/</path>
    <filename>dynamixel_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>BROADCAST_ID</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>ab9fe47395310b34fa1ceb112c9ca10e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INST_PING</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>acb92e93ddd4b53533b14dc3403346bbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INST_READ</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a60599b6587736bb05efb8ea3c5e5f87f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INST_WRITE</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a1c304d06170982719fd605a87c9101f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INST_REG_WRITE</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>ae2afd415cd9007f4688bf77507f0383e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INST_ACTION</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>adea21b73305aa7a5b3317e299c616853</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INST_RESET</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>ad670526ca941302efb4a0d00e7dd43c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INST_SYNC_WRITE</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>aeaa4b61ee11d45bd1a0cb932d7abaf77</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAXNUM_TXPARAM</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>ac6f032d3202471d5f89dc6bd9c620a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERRBIT_VOLTAGE</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>aee0fe36dd0c5a2239a1101cc7f45a957</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERRBIT_ANGLE</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a40737686e1fdb72a93f871c1ab09f547</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERRBIT_OVERHEAT</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>acbae3dabfa09f0fd802fcb7395e2405d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERRBIT_RANGE</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>add7ff9ec439c1a52fc05dcaaa33d940f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERRBIT_CHECKSUM</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a403277a113ea856cd7237e637e73d333</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERRBIT_OVERLOAD</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a0d220ee139359427c11be6d9cf7f456f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERRBIT_INSTRUCTION</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>aabb4fe896a0ebdf7532a632cce3b5a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAXNUM_RXPARAM</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a6f953c9f5eed72413f2c4c1f14d3ca51</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COMM_TXSUCCESS</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>aac6d30f996256b24d311de81eb0f0c1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COMM_RXSUCCESS</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a171328d9f298535c18d079f65e631434</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COMM_TXFAIL</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>af88390c8be18c4079e65fd07b8d553be</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COMM_RXFAIL</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a7a274a04e144aac01bedabaec005fd6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COMM_TXERROR</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a1bd7c7b30db4f56dc80cef65ad38afff</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COMM_RXWAITING</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>ae4b5e71a685506956bf151e3117f3487</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COMM_RXTIMEOUT</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>af9976398353d104bb8a78b1f02f9fceb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COMM_RXCORRUPT</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a93c30bd345d8077112f0a3524d26278b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_initialize</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a76bc731c487991a33bea81364d8926fd</anchor>
      <arglist>(int devIndex, int baudnum)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_terminate</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>aefc7e0cd6b906a79d512a02dae6a9931</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_set_txpacket_id</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a00dacfd9db66ecb5ec893e5cfa59a584</anchor>
      <arglist>(int id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_set_txpacket_instruction</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>abb8666e77863b8cc5b1ab062d0b3caea</anchor>
      <arglist>(int instruction)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_set_txpacket_parameter</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a4b864a289768e19004274a24f048aba7</anchor>
      <arglist>(int index, int value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_set_txpacket_length</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>ad565c67e2fcaea80b11029dc1ab7d0e6</anchor>
      <arglist>(int length)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_get_rxpacket_error</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>ab105aaeede74d37c4b787fa29c5ee043</anchor>
      <arglist>(int errbit)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_get_rxpacket_parameter</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a2f84c42c39f72e16ff0943a759c72b38</anchor>
      <arglist>(int index)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_get_rxpacket_length</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>ac2963412a370d91f3bba984d25c359ad</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_makeword</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a990cec951ec0c2bfaa63c58f40543fd3</anchor>
      <arglist>(int lowbyte, int highbyte)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_get_lowbyte</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a45d451104d0cbf783c31aac57472a0ca</anchor>
      <arglist>(int word)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_get_highbyte</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a82ff77b3d39547a82b08bd9c813c2025</anchor>
      <arglist>(int word)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_tx_packet</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a0f4c3756c1dc8c745c9244f124f14c3e</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_rx_packet</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a3959a369b5088372e6479a4cbf429030</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_txrx_packet</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a6a8152abb99eff55541893ada70ba7e3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_get_result</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>ab953614948f82dcc92243cbe9e5e73d8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_ping</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a355e44903098e49f38899f6de621083d</anchor>
      <arglist>(int id)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_read_byte</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>acdaa030c86e11266821e0be7014f7eb1</anchor>
      <arglist>(int id, int address)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_write_byte</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>aae902702f0ee6862f1f857ec73ed6f29</anchor>
      <arglist>(int id, int address, int value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dxl_read_word</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a140c20005cb976b6b8fc7054fb0dec0e</anchor>
      <arglist>(int id, int address)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dxl_write_word</name>
      <anchorfile>dynamixel_8h.html</anchorfile>
      <anchor>a81ac11c3b986fe32b7040516761bee9f</anchor>
      <arglist>(int id, int address, int value)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>handles.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/io/</path>
    <filename>handles_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>handlesConfigure</name>
      <anchorfile>handles_8h.html</anchorfile>
      <anchor>af6f938cada7412b82bbe6e1d33bacac2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>FILE *</type>
      <name>uart_debug</name>
      <anchorfile>handles_8h.html</anchorfile>
      <anchor>a05bab81533cbbdded38b6b5654ae1f42</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>FILE *</type>
      <name>uart_turret</name>
      <anchorfile>handles_8h.html</anchorfile>
      <anchor>aba037a37cba636f4cf7015218dccdc26</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>FILE *</type>
      <name>spi_ia</name>
      <anchorfile>handles_8h.html</anchorfile>
      <anchor>a506fe7262f43bf520a9b8f8eddc89d32</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>rtsp_api.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/io/</path>
    <filename>rtsp__api_8h</filename>
    <member kind="function">
      <type>int16_t</type>
      <name>flashPageErase</name>
      <anchorfile>rtsp__api_8h.html</anchorfile>
      <anchor>a9272e3cda57e1c49165bb705804a1a3c</anchor>
      <arglist>(uint16_t nvmAdru, uint16_t nvmAdr)</arglist>
    </member>
    <member kind="function">
      <type>int16_t</type>
      <name>flashPageRead</name>
      <anchorfile>rtsp__api_8h.html</anchorfile>
      <anchor>a5099aa7a172a0c8c441736ff649cc5fa</anchor>
      <arglist>(uint16_t nvmAdru, uint16_t nvmAdr, int16_t *pageBufPtr)</arglist>
    </member>
    <member kind="function">
      <type>int16_t</type>
      <name>flashWordRead</name>
      <anchorfile>rtsp__api_8h.html</anchorfile>
      <anchor>a7c65feba1294ae530d4a7460d8a2836a</anchor>
      <arglist>(uint16_t nvmRow, uint16_t nvmOffset, uint16_t nvmAdru, uint16_t nvmAdr, int16_t *wordBufptr)</arglist>
    </member>
    <member kind="function">
      <type>int16_t</type>
      <name>flashPageModify</name>
      <anchorfile>rtsp__api_8h.html</anchorfile>
      <anchor>af0155210dcc78c0351e434d84b10c49c</anchor>
      <arglist>(uint16_t row, uint16_t size, int16_t *rowBuf, int16_t *pageBufPtr)</arglist>
    </member>
    <member kind="function">
      <type>int16_t</type>
      <name>flashPageWrite</name>
      <anchorfile>rtsp__api_8h.html</anchorfile>
      <anchor>afb49afee9cb06c97e961032d4b96725a</anchor>
      <arglist>(uint16_t nvmAdru, uint16_t nvmAdr, int16_t *pageBufPtr)</arglist>
    </member>
    <member kind="function">
      <type>int16_t</type>
      <name>flashWordModify</name>
      <anchorfile>rtsp__api_8h.html</anchorfile>
      <anchor>aec3a652a014e77996ff8c0d336c5df67</anchor>
      <arglist>(uint16_t row, uint16_t offset, uint16_t nvmAdru, uint16_t nvmAdr, int16_t *ModWords)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>spi.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/io/</path>
    <filename>spi_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>spiInit</name>
      <anchorfile>spi_8h.html</anchorfile>
      <anchor>a5b85252785eca03e1a94aa0636c9c9cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>spiClose</name>
      <anchorfile>spi_8h.html</anchorfile>
      <anchor>a53eef1782fff79ce6ecfabf036b7533a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>spiParseRx</name>
      <anchorfile>spi_8h.html</anchorfile>
      <anchor>a11855894fb3016a9e209c7e6dc3da6c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>spiSendTx</name>
      <anchorfile>spi_8h.html</anchorfile>
      <anchor>a968cd78b824442d71bfc17b1df24f030</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>spiQueueFrameRx</name>
      <anchorfile>spi_8h.html</anchorfile>
      <anchor>a648cbc0b6a861c89bde4daacb234544e</anchor>
      <arglist>(frame_t *frame)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>spiQueueFrameTx</name>
      <anchorfile>spi_8h.html</anchorfile>
      <anchor>a25a64bdaebec4ab283bfd88ac4ead563</anchor>
      <arglist>(frame_t *frame)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bits.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/tools/</path>
    <filename>bits_8h</filename>
    <class kind="struct">bitPtr</class>
    <member kind="typedef">
      <type>volatile unsigned int *</type>
      <name>regPtr</name>
      <anchorfile>bits_8h.html</anchorfile>
      <anchor>a1e56a8738c11a970edfbd8dd4c63d95a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct bitPtr</type>
      <name>bitPtr</name>
      <anchorfile>bits_8h.html</anchorfile>
      <anchor>a88ffc5bd84c67666e729622bef78dcbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>bitInit</name>
      <anchorfile>bits_8h.html</anchorfile>
      <anchor>a3f242714a6c7a715ced3b880932ec502</anchor>
      <arglist>(bitPtr *bptr, regPtr reg, unsigned char n)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>bitSet</name>
      <anchorfile>bits_8h.html</anchorfile>
      <anchor>a0c35bac02adff78530790b9fbe635c77</anchor>
      <arglist>(bitPtr bptr, bool b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>bitGet</name>
      <anchorfile>bits_8h.html</anchorfile>
      <anchor>adde24bca3e09103689a304e46f3ae315</anchor>
      <arglist>(bitPtr rb)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>delay.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/tools/</path>
    <filename>delay_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>delay_ms</name>
      <anchorfile>delay_8h.html</anchorfile>
      <anchor>a575761e29fb5dc46b46d5859645fedbe</anchor>
      <arglist>(A)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>delay_us</name>
      <anchorfile>delay_8h.html</anchorfile>
      <anchor>a713a01fc5d2e807d604c091cec30698b</anchor>
      <arglist>(A)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>math.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/tools/</path>
    <filename>math_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>MIN</name>
      <anchorfile>math_8h.html</anchorfile>
      <anchor>a3acffbd305ee72dcd4593c0d8af64a4f</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAX</name>
      <anchorfile>math_8h.html</anchorfile>
      <anchor>afa99ec4acc4ecb2dc3c2d05da15d0e3f</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ABS</name>
      <anchorfile>math_8h.html</anchorfile>
      <anchor>ae2f08dc603ae93c402abd918ba4e23e1</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SIGN</name>
      <anchorfile>math_8h.html</anchorfile>
      <anchor>a8c4a9e5e4622948245de4ec0b5d38329</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SIGN0</name>
      <anchorfile>math_8h.html</anchorfile>
      <anchor>a5f6e49dda825c74fb855c405a29d9e3f</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DIRECTION</name>
      <anchorfile>math_8h.html</anchorfile>
      <anchor>a35c62b7e68603e0ecd2a507d383b9b69</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PI</name>
      <anchorfile>math_8h.html</anchorfile>
      <anchor>a598a3330b3c21701223ee0ca14316eca</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tracker.h</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/tracking/</path>
    <filename>tracker_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>trackerSetObjective</name>
      <anchorfile>tracker_8h.html</anchorfile>
      <anchor>a5e047f9382c71b2fea1ed869a53768d3</anchor>
      <arglist>(float x, float y, float angle)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trackerSetPosition</name>
      <anchorfile>tracker_8h.html</anchorfile>
      <anchor>a39fac0ba8425227d3cd612ee64064b7f</anchor>
      <arglist>(float new_position_x, float new_position_y, float new_position_angle)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trackerUpdate</name>
      <anchorfile>tracker_8h.html</anchorfile>
      <anchor>a47482ae55da8a72c819166663c304b95</anchor>
      <arglist>(unsigned int time_elapsed)</arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>position_x</name>
      <anchorfile>tracker_8h.html</anchorfile>
      <anchor>a23b231f4f8af79d2071b60cbacebfc99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>position_y</name>
      <anchorfile>tracker_8h.html</anchorfile>
      <anchor>af31f30f5c4fab9afb7dedf677d53104b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>position_angle</name>
      <anchorfile>tracker_8h.html</anchorfile>
      <anchor>a5a7c91b4b69ddb8c1c55eee004fbe243</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>objective_x</name>
      <anchorfile>tracker_8h.html</anchorfile>
      <anchor>aa2a46fb3e070d5e55604c3838e104264</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>objective_y</name>
      <anchorfile>tracker_8h.html</anchorfile>
      <anchor>af5beded7dc782d9e595697f784c83b03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>objective_angle</name>
      <anchorfile>tracker_8h.html</anchorfile>
      <anchor>aeb6a5288d136a931ca2e65e69fe0bb8c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>README.md</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/</path>
    <filename>_r_e_a_d_m_e_8md</filename>
  </compound>
  <compound kind="struct">
    <name>bitPtr</name>
    <filename>structbit_ptr.html</filename>
    <member kind="variable">
      <type>regPtr</type>
      <name>reg</name>
      <anchorfile>structbit_ptr.html</anchorfile>
      <anchor>a856e4ce1d2255caeeefd6406765c743d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char</type>
      <name>n</name>
      <anchorfile>structbit_ptr.html</anchorfile>
      <anchor>aa94ff7ddd304b9beb2f209b6174e180e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Controller</name>
    <filename>struct_controller.html</filename>
    <member kind="variable">
      <type>ControllerState</type>
      <name>state</name>
      <anchorfile>struct_controller.html</anchorfile>
      <anchor>a13d80ec6eb384afd4ad6e63242a8ec30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>order_length</name>
      <anchorfile>struct_controller.html</anchorfile>
      <anchor>a88c197418ce2529311e25be397671749</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>order_angle</name>
      <anchorfile>struct_controller.html</anchorfile>
      <anchor>ad8ef90ee6b3fdff728811c92db5477c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>state_initialisation_done</name>
      <anchorfile>struct_controller.html</anchorfile>
      <anchor>a61069155f78b30f4507ef4afa616197c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>PID</type>
      <name>pid_length</name>
      <anchorfile>struct_controller.html</anchorfile>
      <anchor>ab1f3e852c85abd8338288bb8eb2e32ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>PID</type>
      <name>pid_angle</name>
      <anchorfile>struct_controller.html</anchorfile>
      <anchor>ae06d984d89427c551833ed33f319dedd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>PID</type>
      <name>pid_speed</name>
      <anchorfile>struct_controller.html</anchorfile>
      <anchor>aa167c26394de7dee4e203f4a8545363e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>threshold_length</name>
      <anchorfile>struct_controller.html</anchorfile>
      <anchor>a1f65f2ae13f370767e7e07e8860949e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>calibration_order</name>
      <anchorfile>struct_controller.html</anchorfile>
      <anchor>a1a03f232b994eae849a2f4c402bf3800</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>speed_max_order</name>
      <anchorfile>struct_controller.html</anchorfile>
      <anchor>aafd01b4d1cd08660a10e1bff9247d62e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Encoder</name>
    <filename>struct_encoder.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>old_value</name>
      <anchorfile>struct_encoder.html</anchorfile>
      <anchor>a14e6c22e7c6e39728374f864762f30bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>new_value</name>
      <anchorfile>struct_encoder.html</anchorfile>
      <anchor>a65e477692f3f5500b90b4c49cc962759</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int16_t</type>
      <name>variation</name>
      <anchorfile>struct_encoder.html</anchorfile>
      <anchor>ae174cd00a4a00eb4cdf062da2890992c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>mm_per_tick</name>
      <anchorfile>struct_encoder.html</anchorfile>
      <anchor>a81ba938164c3e6af7492aa3c6350dd78</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>rad_per_tick</name>
      <anchorfile>struct_encoder.html</anchorfile>
      <anchor>a1ad8b865f325511625410482ed0ce70c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>PID</name>
    <filename>struct_p_i_d.html</filename>
    <member kind="variable">
      <type>float</type>
      <name>param_P</name>
      <anchorfile>struct_p_i_d.html</anchorfile>
      <anchor>a522f30d0196be1a9d681bf6cd7312079</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>param_I</name>
      <anchorfile>struct_p_i_d.html</anchorfile>
      <anchor>a5da4dcc00d98a6bc96c2f6e73109ac40</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>param_D</name>
      <anchorfile>struct_p_i_d.html</anchorfile>
      <anchor>ae98eb274705d1f1c830b84d6b85b058e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>last_error</name>
      <anchorfile>struct_p_i_d.html</anchorfile>
      <anchor>a53bf2ded26ca455e1227890c20123cd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>accumulator</name>
      <anchorfile>struct_p_i_d.html</anchorfile>
      <anchor>a46eb7da1d21fab45d611c90e42c1eae8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>include/ai</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/ai/</path>
    <filename>dir_9f94a405e787828644b412ab81725f16.html</filename>
    <file>ai.h</file>
  </compound>
  <compound kind="dir">
    <name>include/control</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/control/</path>
    <filename>dir_a4935814f13a540f683bf390f3273be3.html</filename>
    <file>controller.h</file>
    <file>encoders.h</file>
    <file>motors.h</file>
    <file>pid.h</file>
  </compound>
  <compound kind="dir">
    <name>include/debug</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/debug/</path>
    <filename>dir_0ca87e0e155b63d3277a4a8052f2e1d0.html</filename>
    <file>leds.h</file>
    <file>log.h</file>
  </compound>
  <compound kind="dir">
    <name>include</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/</path>
    <filename>dir_d44c64559bbebec7f509842c48db8b23.html</filename>
    <dir>include/ai</dir>
    <dir>include/control</dir>
    <dir>include/debug</dir>
    <dir>include/io</dir>
    <dir>include/tools</dir>
    <dir>include/tracking</dir>
  </compound>
  <compound kind="dir">
    <name>include/io</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/io/</path>
    <filename>dir_a00b633439466cbb1729245c7f66f564.html</filename>
    <file>adc.h</file>
    <file>config_flash.h</file>
    <file>dxl_hal.h</file>
    <file>dynamixel.h</file>
    <file>handles.h</file>
    <file>rtsp_api.h</file>
    <file>spi.h</file>
  </compound>
  <compound kind="dir">
    <name>include/tools</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/tools/</path>
    <filename>dir_db22b1395f615d1428e10e22469fe87b.html</filename>
    <file>bits.h</file>
    <file>delay.h</file>
    <file>math.h</file>
  </compound>
  <compound kind="dir">
    <name>include/tracking</name>
    <path>/home/Brice/GaliVII/Prog/GaLib.X/include/tracking/</path>
    <filename>dir_7dd526ae9727a8c39b13b3c6769aa6c4.html</filename>
    <file>tracker.h</file>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title></title>
    <filename>index</filename>
  </compound>
</tagfile>
