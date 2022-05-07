[top]
components : flipflop@Process clk@Signal d@Signal q@Signal
out : q
in  : d clk
Link : out@clk clk@flipflop
Link : out@d d@flipflop
Link : q@flipflop in@q
Link : out@q q
Link : clk in@clk
Link : d in@d

[q]
Transport_Delay : 00:00:00:100

[clk]
Transport_Delay : 00:00:00:010

[d]
Transport_Delay : 00:00:00:000


