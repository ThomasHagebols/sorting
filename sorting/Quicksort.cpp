int quickSort(long long values[], int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = values[(left + right) / 2];

	/* partition */
	while (i <= j) {
		while (values[i] < pivot)
			i++;
		while (values[j] > pivot)
			j--;
		if (i <= j) {
			tmp = values[i];
			values[i] = values[j];
			values[j] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSort(values, left, j);
	if (i < right)
		quickSort(values, i, right);
	return 0;
}