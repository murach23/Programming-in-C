(
  ( SET A ' 1 ' )
  ( PRINT A )
  ( SET B ' 2 ' )
  ( PRINT B )
  ( SET C B )
  ( PRINT C )
  ( SET D ( LESS B C ) )
  ( PRINT D )
  ( SET E ( PLUS ' 5 ' B ) )
  ( PRINT E )
  ( SET F ' ( 2 3 ) ' )
  ( PRINT F )
  ( SET G ( LENGTH F ) )
  ( PRINT G )
  ( SET H ( CONS A F ) )
  ( PRINT H )
  ( SET I ( CONS ' 5 ' ' ( 6 7 ) ' ) )
  ( PRINT I )
  ( SET J ( CONS ' 1 ' ( CONS ' 2 ' NIL ) ) )
  ( PRINT J ) 
  ( SET K ' ( 1 2 3 ( 4 5 ) 6 ) ' )
  ( PRINT K )
)
