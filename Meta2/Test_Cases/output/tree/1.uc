Program
..Declaration
....Int
....Id(a)
....IntLit(0)
..Declaration
....Int
....Id(b)
..Declaration
....Int
....Id(c)
..Declaration
....Short
....Id(d)
..Declaration
....Short
....Id(e)
..Declaration
....Short
....Id(f)
....IntLit(0)
..Declaration
....Char
....Id(g)
..Declaration
....Char
....Id(h)
..Declaration
....Char
....Id(i)
....ChrLit('a')
..Declaration
....Void
....Id(j)
..Declaration
....Void
....Id(k)
..Declaration
....Void
....Id(l)
..FuncDeclaration
....Int
....Id(main)
....ParamList
......ParamDeclaration
........Void
..FuncDeclaration
....Int
....Id(declarations)
....ParamList
......ParamDeclaration
........Int
......ParamDeclaration
........Short
......ParamDeclaration
........Char
........Id(c)
......ParamDeclaration
........Double
......ParamDeclaration
........Void
..FuncDeclaration
....Short
....Id(stat_and_expr)
....ParamList
......ParamDeclaration
........Int
........Id(a)
......ParamDeclaration
........Int
......ParamDeclaration
........Int
......ParamDeclaration
........Int
........Id(d)
..FuncDefinition
....Int
....Id(main)
....ParamList
......ParamDeclaration
........Void
....FuncBody
......Declaration
........Char
........Id(i)
........ChrLit('A')
......While
........Le
..........Id(i)
..........ChrLit('Z')
........StatList
..........Call
............Id(putchar)
............Id(i)
..........Store
............Id(i)
............Add
..............Id(i)
..............IntLit(1)
......Return
........IntLit(0)
..FuncDefinition
....Double
....Id(declarations)
....ParamList
......ParamDeclaration
........Int
........Id(i)
......ParamDeclaration
........Short
........Id(s)
......ParamDeclaration
........Char
........Id(c)
......ParamDeclaration
........Double
........Id(d)
......ParamDeclaration
........Void
........Id(v)
....FuncBody
......Declaration
........Int
........Id(i1)
......Declaration
........Int
........Id(i2)
......Declaration
........Int
........Id(i3)
......Declaration
........Short
........Id(s1)
......Declaration
........Short
........Id(s2)
......Declaration
........Short
........Id(s3)
......Declaration
........Char
........Id(c1)
......Declaration
........Char
........Id(c2)
......Declaration
........Char
........Id(c3)
......Declaration
........Double
........Id(d1)
......Declaration
........Double
........Id(d2)
......Declaration
........Double
........Id(d3)
......Declaration
........Void
........Id(v1)
......Declaration
........Void
........Id(v2)
......Declaration
........Void
........Id(v3)
......Declaration
........Int
........Id(i4)
........IntLit(0)
......Declaration
........Int
........Id(i5)
........IntLit(0)
......Declaration
........Int
........Id(i6)
........IntLit(0)
......Declaration
........Short
........Id(s4)
........IntLit(0)
......Declaration
........Short
........Id(s5)
........IntLit(0)
......Declaration
........Short
........Id(s6)
........IntLit(0)
......Declaration
........Char
........Id(c4)
........IntLit(0)
......Declaration
........Char
........Id(c5)
........IntLit(0)
......Declaration
........Char
........Id(c6)
........IntLit(0)
......Declaration
........Double
........Id(d4)
........RealLit(0.0)
......Declaration
........Double
........Id(d5)
........RealLit(0.0)
......Declaration
........Double
........Id(d6)
........RealLit(0.0)
......Declaration
........Void
........Id(v4)
........IntLit(0)
......Declaration
........Void
........Id(v5)
........IntLit(0)
......Declaration
........Void
........Id(v6)
........IntLit(0)
......Return
........Id(d)
..FuncDefinition
....Short
....Id(stat_and_expr)
....ParamList
......ParamDeclaration
........Int
........Id(a)
......ParamDeclaration
........Int
........Id(b)
......ParamDeclaration
........Int
........Id(c)
......ParamDeclaration
........Int
........Id(d)
....FuncBody
......Declaration
........Short
........Id(s)
........ChrLit('\000')
......Store
........Id(a)
........BitWiseOr
..........Mul
............Comma
..............Add
................Id(b)
................Id(c)
..............Add
................Id(d)
................Id(e)
............Id(d)
..........BitWiseAnd
............Id(a)
............Sub
..............Id(b)
..............Minus
................And
..................Id(a)
..................Id(b)
......Return
........Id(s)
..Declaration
....Int
....Id(expr1)
....Mul
......BitWiseAnd
........Comma
..........Add
............IntLit(1)
............IntLit(1)
..........Add
............IntLit(2)
............IntLit(2)
........Add
..........Id(a)
..........Id(b)
......Minus
........Comma
..........Plus
............Comma
..............Minus
................Id(c)
..............Id(d)
..........Id(e)