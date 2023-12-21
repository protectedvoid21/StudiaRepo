def fibTuple(m: Int): (Int, Int) = {
    var previousElement = 1
    var currentElement = 1

    for (i <- 3 to m) 
        var temp = currentElement
        currentElement += previousElement
        previousElement = temp
    
    (previousElement, currentElement)
}

fibTuple(1)
fibTuple(2)
fibTuple(3)
fibTuple(4)
fibTuple(10)
    
def fibArray(count: Int, firstTerm: Int, secondTerm: Int): Array[Int] = {
    if count < 1 then return Array()
    if count == 1 then return Array(firstTerm)

    var fibArray = new Array[Int](count)
    fibArray(0) = firstTerm
    fibArray(1) = secondTerm

    for (i <- 2 to count - 1) 
        fibArray(i) = fibArray(i - 1) + fibArray(i - 2)
    
    fibArray
}


def imperacci(m: Int, n: Int): Array[Int] = {
    if n < 1 then return Array()
    
    var offsetFibTuple = fibTuple(m * 2)
    if n == 1 then return Array(offsetFibTuple._1)
    if n == 2 then return Array(offsetFibTuple._1, offsetFibTuple._2)

    fibArray(n, offsetFibTuple._1, offsetFibTuple._2)
}

imperacci(1, 10).toList
imperacci(2, 10).toList
imperacci(3, 10).toList
imperacci(4, 10).toList
imperacci(5, 10).toList
imperacci(6, 10).toList
imperacci(7, 10).toList
imperacci(8, 10).toList
imperacci(9, 10).toList
imperacci(10, 10).toList