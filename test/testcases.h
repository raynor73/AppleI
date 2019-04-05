static uint8_t calculateP(const uint8_t variant) {
	return (variant & 0x1f) | ((variant << 1) & 0xc0);
}

static void testOraIndirectX(QWidget *parent) {
	qDebug("Starting ORA Indirect X test");

	Mos6502::Cpu cpu;
	cpu.isDebugMode = false;

	TestMemory testMemory;
	cpu.memory = &testMemory;

	const uint8_t maxA = 0xff;
	const uint8_t maxMem = 0xff;
	const uint8_t maxP = 0x7f;
	const int numberOfMemoryVariants = 2;

	const int totalVariants = (maxA + 1) * (maxMem + 1) * (maxP + 1) * numberOfMemoryVariants;
	int currentVariant = 0;
	float prevProgress = -1;

	/*QProgressDialog progress("Testing ORA Indirect X", "Abort", 0, totalVariants, parent);
	progress.setWindowModality(Qt::WindowModal);
	progress.setMinimumDuration(0);*/

	std::map<uint16_t, uint8_t> initialMemoryState;
	for (int memoryVariant = 0; memoryVariant < numberOfMemoryVariants; memoryVariant++) {
		initialMemoryState.clear();
		uint8_t x;
		switch (memoryVariant) {
		case 0:
			initialMemoryState[0x0080] = 0x01;
			initialMemoryState[0x0081] = 0x04;
			initialMemoryState[0x0300] = 0x01;
			initialMemoryState[0x0301] = 0x80;
			x = 0x00;
			break;

		case 1:
			initialMemoryState[0x00ff] = 0x01;
			initialMemoryState[0x0000] = 0x04;
			initialMemoryState[0x0300] = 0x01;
			initialMemoryState[0x0301] = 0x80;
			x = 0x7f;
			break;
		};
		for (uint16_t aOperand = 0; aOperand <= maxA; aOperand++) {
			for (uint16_t memOperand = 0; memOperand <= maxMem; memOperand++) {
				initialMemoryState[0x0401] = memOperand;
				for (uint8_t pVariant = 0; pVariant <= maxP; pVariant++) {
					//progress.setValue(totalVariants / 2);
					float currentProgress = (float) currentVariant / totalVariants;
					if (prevProgress + 0.1 < currentProgress) {
						prevProgress = currentProgress;
						qDebug("%f", currentProgress);
					}
					currentVariant++;

					/*if (progress.wasCanceled()) {
						qDebug("ORA Indirect X test canceled");
						return;
					}*/

					CpuState initialCpuState(aOperand, x, 0x00, 0x00, 0x0300, calculateP(pVariant));

					TestCase testCase(&cpu, &testMemory, initialCpuState, &initialMemoryState);
					testCase.performTest();
					if (!testCase.passed()) {
						qDebug("ORA Indirect X test failed");
						return;
					}
				}
			}
		}
	}
	//progress.setValue(totalVariants);

	qDebug("ORA Indirect X test passed");
}

static void testOraZeroPage() {
	qDebug("Starting ORA Zero Page test");

	Mos6502::Cpu cpu;
	cpu.isDebugMode = false;

	TestMemory testMemory;
	cpu.memory = &testMemory;

	const uint8_t maxA = 0xff;
	const uint8_t maxMem = 0xff;
	const uint8_t maxP = 0x7f;

	const int totalVariants = (maxA + 1) * (maxMem + 1) * (maxP + 1);
	int currentVariant = 0;
	float prevProgress = -1;

	std::map<uint16_t, uint8_t> initialMemoryState;
	initialMemoryState[0x0300] = 0x05;
	initialMemoryState[0x0301] = 0x80;
	for (uint16_t aOperand = 0; aOperand <= maxA; aOperand++) {
		for (uint16_t memOperand = 0; memOperand <= maxMem; memOperand++) {
			initialMemoryState[0x0080] = memOperand;
			for (uint8_t pVariant = 0; pVariant <= maxP; pVariant++) {
				float currentProgress = (float) currentVariant / totalVariants;
				if (prevProgress + 0.1 < currentProgress) {
					prevProgress = currentProgress;
					qDebug("%f", currentProgress);
				}
				currentVariant++;

				CpuState initialCpuState(aOperand, 0x00, 0x00, 0x00, 0x0300, calculateP(pVariant));

				TestCase testCase(&cpu, &testMemory, initialCpuState, &initialMemoryState);
				testCase.performTest();
				if (!testCase.passed()) {
					qDebug("ORA Zero Page test failed");
					return;
				}
			}
		}
	}

	qDebug("ORA Zero Page test passed");
}

static void testAslZeroPage() {
	const char *testName = "ASL Zero Page";
	qDebug("Starting %s test", testName);

	Mos6502::Cpu cpu;
	cpu.isDebugMode = false;

	TestMemory testMemory;
	cpu.memory = &testMemory;

	const uint8_t maxMem = 0xff;
	const uint8_t maxP = 0x7f;

	const int totalVariants = (maxMem + 1) * (maxP + 1);
	int currentVariant = 0;
	float prevProgress = -1;

	std::map<uint16_t, uint8_t> initialMemoryState;
	initialMemoryState[0x0300] = 0x06;
	initialMemoryState[0x0301] = 0x80;
	for (uint16_t memOperand = 0; memOperand <= maxMem; memOperand++) {
		initialMemoryState[0x0080] = memOperand;
		for (uint8_t pVariant = 0; pVariant <= maxP; pVariant++) {
			float currentProgress = (float) currentVariant / totalVariants;
			if (prevProgress + 0.1 < currentProgress) {
				prevProgress = currentProgress;
				qDebug("%f", currentProgress);
			}
			currentVariant++;

			CpuState initialCpuState(0x00, 0x00, 0x00, 0x00, 0x0300, calculateP(pVariant));

			TestCase testCase(&cpu, &testMemory, initialCpuState, &initialMemoryState);
			testCase.performTest();
			if (!testCase.passed()) {
				qDebug("%s test failed", testName);
				return;
			}
		}
	}

	qDebug("%s test passed", testName);
}

static void testPhp() {
	const char *testName = "PHP";
	qDebug("Starting %s test", testName);

	Mos6502::Cpu cpu;
	cpu.isDebugMode = false;

	TestMemory testMemory;
	cpu.memory = &testMemory;

	const uint8_t maxP = 0x7f;

	const int totalVariants = (maxP + 1);
	int currentVariant = 0;
	float prevProgress = -1;

	std::map<uint16_t, uint8_t> initialMemoryState;
	initialMemoryState[0x0300] = 0x08;
	for (uint8_t pVariant = 0; pVariant <= maxP; pVariant++) {
		float currentProgress = (float) currentVariant / totalVariants;
		if (prevProgress + 0.1 < currentProgress) {
			prevProgress = currentProgress;
			qDebug("%f", currentProgress);
		}
		currentVariant++;

		CpuState initialCpuState(0x00, 0x00, 0x00, 0xff, 0x0300, calculateP(pVariant));

		TestCase testCase(&cpu, &testMemory, initialCpuState, &initialMemoryState);
		testCase.performTest();
		if (!testCase.passed()) {
			qDebug("%s test failed", testName);
			return;
		}
	}

	qDebug("%s test passed", testName);
}
