import sys
import re
this=open("../doc/g12_prof_report.tex",'r')
ya=open("../doc/g12_lab09_report.html",'w')
aa=this.read()
ans=re.findall(r'\\section{Timing}.*\\subsection{Differece in gettimeofday and time}',aa,re.DOTALL)
ans=re.sub(r'(\\section{)(.*)(})',r'<h1>\2</h1>',ans[0],re.DOTALL)
ans=re.sub(r'(\\subsection{)(.*)(})',r'<h2>\2</h2>',ans,re.DOTALL)
ans=re.sub(r'<h2>.*</h2>$',r'',ans,re.DOTALL)
ans=re.sub(r'\\begin{center}',r'<div align="center">',ans,re.DOTALL)
ans=re.sub(r'\\end{center}',r'</div>',ans,re.DOTALL)
ans=re.sub(r'\\begin{itemize}',r'<ul>',ans,re.DOTALL)
ans=re.sub(r'\\end{itemize}',r'</ul>',ans,re.DOTALL)
ans=re.sub(r'\\item',r'<li>',ans,re.DOTALL)
ans=re.sub(r'(\\includegraphics)(.*)({)(.*)(})',r'<img src="../plots/\4.png" </img>',ans,re.DOTALL)
ans=re.sub(r'\\\\',r'<br>',ans,re.DOTALL)
ya.write("""<!DOCTYPE HTML>
<html>
<head><title>HTML file of lab 09</title> </head>
<body style="margin-left:50px;margin-right:50px;margin-bottom:50px">
""")
ya.write(ans)
ya.write("""</body>
</html>""")
