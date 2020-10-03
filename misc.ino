

boolean regular_execution(uint32_t *lastExecution, uint32_t REPEATING_INTERVAL)
{
  //does help to regular execute a repeating task like checking for a display update
  if ((millis() - *lastExecution) >= REPEATING_INTERVAL)
  {
    *lastExecution = millis();
    return true;
  }
  return false;
}
