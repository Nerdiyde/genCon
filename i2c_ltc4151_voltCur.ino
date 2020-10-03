void init_ltc4151()
{
  ltc4151_recitifier_input.init(LTC4151::L, LTC4151::L);
}

void read_recitifier_data()
{
  Serial.print("getLoadCurrent: ");
  Serial.println(ltc4151_recitifier_input.getLoadCurrent_mA());
  
  //Serial.print("getSnapshotLoadCurrent: ");
  //Serial.println(ltc4151_recitifier_input.getSnapshotLoadCurrent(0.1));
  
  Serial.print("getInputVoltage: ");
  Serial.println(ltc4151_recitifier_input.getInputVoltage());
  
  //Serial.print("getSnapshotInputVoltage: ");
  //Serial.println(ltc4151_recitifier_input.getSnapshotInputVoltage());
  
  //Serial.print("getADCInVoltage: ");
  //Serial.println(ltc4151_recitifier_input.getADCInVoltage());
  
  //Serial.print("getSnapshotADCInVoltage: ");
  //Serial.println(ltc4151_recitifier_input.getSnapshotADCInVoltage());
  Serial.println();
}
