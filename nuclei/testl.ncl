(
   ( IF ( EQUAL ( LENGTH NIL ) ' 0 ' ) ( ( PRINT " NIL HAS ZERO LENGTH " ) ) ( ( PRINT " FAILURE " ) ) )
   ( IF ( EQUAL ( LENGTH ' (1) ' ) ' 0 ' ) ( ( PRINT " FAILURE " ) ) ( ( PRINT " (1) DOESN'T HAVE ZERO LENGTH " ) ) )
   ( IF ( EQUAL ( LENGTH A ) ' 0 ' )  ( ( PRINT " A HAS ZERO LENGTH " ) ) ( ( PRINT " FAILURE " ) ) )
   ( SET L ( CONS ' 2 ' NIL ) )
   ( PRINT L )
   ( IF ( EQUAL ( CAR L ) ' 2 ' )  ( ( PRINT " L1 has Car 2 " ) ) ( ( PRINT " FAILURE " ) ) )
   ( PRINT M )
   ( SET N ( CONS ' 1 ' L ) )
   ( PRINT N )
   ( SET P ( CONS N M ) )
   ( PRINT P )
)

//comments
 deleted one 
