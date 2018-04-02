int solve(int digits, int sum) {
	int m = 1000000007;
	if (digits == 1) {
		return sum <= 9;
	}

	vector<unsigned long long>save(sum+1, 0);
	for (int num = 1; num <= sum && num<=9; ++num) {
		++save[num];
	}

	for (int iter = 2; iter <= digits; ++iter) {
		vector<unsigned long long>new_save(sum + 1, 0);
		for (int idx = 1; idx < save.size(); ++idx) {
			if (save[idx] == 0) {
				continue;
			}
			for (int add = 0; add <= 9; ++add) {
				if (idx + add > sum) {
					break;
				}
				new_save[idx + add]+=save[idx];
				new_save[idx + add] %= m;
			}
		}
		save = new_save;
	}
	return save.back();
} // time O(digits * sum * 9); space O(sum)