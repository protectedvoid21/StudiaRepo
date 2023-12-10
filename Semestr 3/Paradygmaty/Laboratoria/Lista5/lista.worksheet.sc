def skipTakeL[A](list: LazyList[A]): LazyList[A] = {
    def helper(list: LazyList[A], offset: Int, counter: Int): LazyList[A] =
        list match
            case LazyList() => LazyList()
            case x #:: xs =>
                if counter == offset then
                    x #:: helper(xs, offset + 1, 1)
                else
                    helper(xs, offset, counter + 1)
            
    helper(list, 1, 1)
}

skipTakeL(LazyList.from(1 to 100)).toList
skipTakeL(LazyList.from(-30 to 150)).toList
skipTakeL(LazyList()).toList