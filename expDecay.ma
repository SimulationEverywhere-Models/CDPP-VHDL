
[top]
components : int@rkIntegModel clock 
out : clk y 

Link : y@int y
Link : y@int dydt@int
Link : out@clock clk
Link : out@clock vin@int

[int]
y0 : 0
dydt0 : 0
C : 1.0E-6
R : 1000

[clock]
components : inv@Process_Inv sig1@Signal qm@QuantumMultiply
out : out
Link : out@sig1 in@inv
Link : out@inv  in@sig1
Link : out@sig1 in@qm
Link : out@qm   out

[sig1]
Transport_Delay : 00:00:1:000

[qm]
Transport_Delay : 00:00:00:000
Attenuation : 100



