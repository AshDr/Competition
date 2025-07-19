// get 1~N prime
auto sieve = [&](int N) {
  vector<int> not_prime(N + 1);
  for (int i = 2; i * i <= N; i++) { // accelerate 1
    if (not_prime[i]) continue;
    for (int j = i * i; j <= N; j += i) { // accelerate 2
      not_prime[j] = 1;
    }
  }
  vector<int> prime;
  for (int i = 2; i <= N; i++) {
    if (not_prime[i] == 0) prime.push_back(i);
  }
  return prime;
};