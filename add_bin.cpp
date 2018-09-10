string addBinary(string a, string b){
	int i = a.size() - 1;
	int j = b.size() - 1;
	int res = "";
	int carry = 0;
	while(i >= 0 || j >= 0 || carry){
		long sum =0;
		if(i >= 0){sum += a[i--] - '0';}
        if(j >= 0){sum += b[j--] - '0';}
		sum += carry;
		carry = sum / 2;
		sum %= 2;
		
		res = res + char(sum + '0');
	}
	
	reverse(res.begin(), res.end());
	return res;
}

	
