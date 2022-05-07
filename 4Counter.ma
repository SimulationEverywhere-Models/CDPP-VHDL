[top]
components : 4count@Process_4_Counter b1@Signal b2@Signal b3@Signal b4@Signal clock
out : bo1 bo2 bo3 bo4
link : out@clock clk@4count
link : q1@4count in@b1
link : q2@4count in@b2
link : q3@4count in@b3
link : q4@4count in@b4
link : out@b1 d1@4count
link : out@b2 d2@4count
link : out@b3 d3@4count
link : out@b4 d4@4count
link : out@b1 bo1
link : out@b2 bo2
link : out@b3 bo3
link : out@b4 bo4

[clock]
components : inv@Process_Inv sig1@Signal
out : out
Link : out@sig1 in@inv
Link : out@inv  in@sig1
Link : out@sig1 out

[b1]
Transport_Delay : 00:00:00:000

[b2]
Transport_Delay : 00:00:00:000

[b3]
Transport_Delay : 00:00:00:000

[b4]
Transport_Delay : 00:00:00:000

[sig1]
Transport_Delay : 00:00:00:010
