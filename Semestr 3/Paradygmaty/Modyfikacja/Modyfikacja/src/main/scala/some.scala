object some {
  def main(args: Array[String]): Unit = {
    def argmax(list: List[Int]): (Int, Int) = {
      def aux(lst: List[Int], minTuple: (Int, Int), maxTuple: (Int, Int), index: Int): (Int, Int) = {
        println("ddd")
        if lst == Nil then
          (minTuple._1, maxTuple._1)
        else {
          val checkedMinTuple = if lst.head < minTuple._2 then (index, lst.head) else minTuple
          val checkedMaxTuple = if lst.head > maxTuple._2 then (index, lst.head) else maxTuple
          aux(lst.tail, checkedMinTuple, checkedMaxTuple, index + 1)
        }
      }
      aux(list, (0, list.head), (0, list.head), 0)
    }

    argmax(List(1, 2, 3, 4, 3, 2))
  }
}
