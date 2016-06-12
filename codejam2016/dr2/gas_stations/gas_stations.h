int GetNumKms() {
  return 4;
};

int GetTankSize() {
  return 2;
};

int GetGasPrice(int i) {
  switch (i) {
    case 0:
	return 4;
    case 1:
	return 2;
    case 2:
	return 4;
    case 3:
	return 1;
  }
};
