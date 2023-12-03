def primes(n: Int): List[Int] = {
    def isPrime(x: Int): Boolean = {
        val dividers = for(i <- List.range(2, math.sqrt(x + 1).toInt + 1) if x % i == 0) yield i
        dividers.isEmpty
    }
    for (num <- List.range(2, n + 1) if isPrime(num)) yield num;
}
    
primes(11)
primes(100)
primes(2)