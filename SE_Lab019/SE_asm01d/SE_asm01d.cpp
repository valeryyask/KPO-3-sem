extern "C" {
    int  getmin(int* arr, int len) {
        int min = arr[0];
        for (int i = 1; i < len; ++i) {
            if (arr[i] < min) {
                min = arr[i];
            }
        }
        return min;
    }

    int  getmax(int* arr, int len) {
        int max = arr[0];
        for (int i = 1; i < len; ++i) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        return max;
    }
}

