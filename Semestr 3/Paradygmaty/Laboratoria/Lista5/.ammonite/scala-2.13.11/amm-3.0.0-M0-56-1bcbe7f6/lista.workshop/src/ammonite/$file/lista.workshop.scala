
package ammonite
package $file
import _root_.ammonite.interp.api.InterpBridge.{
  value => interp
}
import _root_.ammonite.interp.api.InterpBridge.value.{
  exit,
  scalaVersion
}
import _root_.ammonite.interp.api.IvyConstructor.{
  ArtifactIdExt,
  GroupIdExt
}
import _root_.ammonite.compiler.CompilerExtensions.{
  CompilerInterpAPIExtensions,
  CompilerReplAPIExtensions
}
import _root_.ammonite.runtime.tools.{
  browse,
  grep,
  time,
  tail
}
import _root_.ammonite.compiler.tools.{
  desugar,
  source
}
import _root_.mainargs.{
  arg,
  main
}
import _root_.ammonite.repl.tools.Util.{
  PathRead
}
import _root_.ammonite.repl.ReplBridge.value.{
  codeColorsImplicit
}


object `lista.workshop`{
/*<script>*/def skipTakeL[A](list: LazyList[A]): LazyList[A] = {
    def helper(list: LazyList[A], offset: Int, counter: Int): LazyList[A] =
        list match
            case LazyList() => LazyList()
            case x #:: xs =>
                if counter == offset then
                    x #:: helper(xs, offset + 1, 1)
                else
                    helper(xs, offset, counter + 1)
            
    helper(list, 2, 1)
}

/*<amm>*/val res_1 = /*</amm>*/skipTakeL(LazyList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10))/*</script>*/ /*<generated>*/
def $main() = { _root_.scala.Iterator[String]() }
  override def toString = "lista$u002Eworkshop"
  /*</generated>*/
}
