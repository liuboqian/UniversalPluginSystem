import json

class PowerCalculator:

  def __init__(self):
    pass

  def name(self):
    return "PowerCalculator"

  def set(self, param):
    raise NotImplementedError()

  def unset(self, param):
    raise NotImplementedError()

  def invoke(self, param):
    data=json.loads(param)
    result = pow(data["a"], data["b"])
    return json.dumps(result)

def name():
  return "PowerCalculator"

def createPlugin():
  return PowerCalculator()

def deletePlugin(plugin):
  del plguin


if __name__=="__main__":
  print(name())
  calculator=createPlugin()
  print(calculator.name())
  param={"a":2,"b":3}
  result=calculator.invoke(json.dumps(param))
  print(result)
