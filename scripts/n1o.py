

class MyObj:
	def __init__(self, name):
		self.name = name
	def __add__(self, rhs):
		if not isinstance(rhs, MyObj):
			raise TypeError("Not a MyObj")
		return self
	def print(self):
		print("This is ", self.name)


if __name__ == "__main__":
	a = MyObj("Stan")
	b = MyObj("Kyle")
	c = a + b
	c.print()
