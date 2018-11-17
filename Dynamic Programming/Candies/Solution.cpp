//Problem URL:
//https://www.hackerrank.com/challenges/candies/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming

#include <bits/stdc++.h>
using namespace std;

/////Code I wrote/////////////////////
// Complete the candies function below.
long candies(int n, vector<int> arr) {
	//array of candy counts for each index
	vector<int> candy(arr.size());
	//candy[0] has a value of at least 1
	candy[0] = 1;
	for (int i = 1; i < arr.size(); ++i) {
		//increase the candie counts while the ratings are rising
		//the index where the incrementing stops is considered a peak
		if (arr[i - 1] < arr[i]) candy[i] = candy[i - 1] + 1;
		//else the candy count for the rating is equal to 1, the values will be incremented if needed in the second loop
		else candy[i] = 1;
	}
	//total candy count is initialized to the candy count for the last index of the candy count array
	long total = candy[candy.size() - 1];
	for (int i = arr.size() - 2; i >= 0; --i) {
		long tmp = 0;
		//increments the candy count if the ratings are rising when traversing in reverse order
		if (arr[i] > arr[i + 1]) tmp = candy[i + 1] + 1;
		//following line ensures that a peak is not overwritten with a lower value.
		//candy[i] would only have a greater value if it is indeed a peak from the first for loop
		candy[i] = (candy[i] > tmp) ? candy[i] : tmp; 
		//totals the candy count for each index
		total += candy[i];
	}
	return total;
}
//////////////////////////////////////

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<int> arr(n);

	for (int i = 0; i < n; i++) {
		int arr_item;
		cin >> arr_item;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		arr[i] = arr_item;
	}

	long result = candies(n, arr);

	fout << result << "\n";

	fout.close();

	return 0;
}
