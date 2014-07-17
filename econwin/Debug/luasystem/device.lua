--设备驱动
model ={};


--创建新的107模块
function new107(id)
	--调用C接口
	tdevice107_init(id);

	local t = {};
	t.outport = {};
	t.outport.outportval = {out0=false;out1=false;out2=false;out3=false;out4=false;out5=false;out6=false;out7=false};

	t.outport.mt = {};
	t.outport.mt.__index = t.outport.outportval;
	t.outport.mt.__newindex = function(tb,k,v)
		if(type(v) == "number") then
			if(v == 0) then
				tb.outportval[k] = false;
			else
				tb.outportval[k] = true;
			end

		elseif(type(v) == "boolean") then
			tb.outportval[k] = v;
		end
	end
	setmetatable(t.outport,t.outport.mt);

	t.inport = {};
	t.inport.inportval = {in0=false;in1=false;in2=false;in3=false;in4=false;in5=false;in6=false;in7=false};
	t.inport.mt = {};
	t.inport.mt.__index = t.inport.inportval;
	t.inport.mt.__newindex = function(tb,k,v)
		if(type(v) == "number") then
			if(v == 0) then
				tb.inportval[k] = false;
			else
				tb.inportval[k] = true;
			end

		elseif(type(v) == "boolean") then
			tb.inportval[k] = v;
		end
	end
	setmetatable(t.inport,t.inport.mt);

	model[id] = t;
	return t;
end

--
function set107inport(id,in0,in1,in2,in3,in4,in5,in6,in7)
	model[id].inport.in0 = in0;
	model[id].inport.in1 = in1;
	model[id].inport.in2 = in2;
	model[id].inport.in3 = in3;
	model[id].inport.in4 = in4;
	model[id].inport.in5 = in5;
	model[id].inport.in6 = in6;
	model[id].inport.in7 = in7;
end

function get107outport(id)

	local allbit = 0;
	if(model[id].outport.out0) then
		allbit = allbit + 1;
	end
	if(model[id].outport.out1) then
		allbit = allbit + 2;
	end
	if(model[id].outport.out2) then
		allbit = allbit + 4;
	end
	if(model[id].outport.out3) then
		allbit = allbit + 8;
	end
	if(model[id].outport.out4) then
		allbit = allbit + 16;
	end
	if(model[id].outport.out5) then
		allbit = allbit + 32;
	end
	if(model[id].outport.out6) then
		allbit = allbit + 64;
	end
	if(model[id].outport.out7) then
		allbit = allbit + 128;
	end
	return allbit;

end

function set107outport(id,out0,out1,out2,out3,out4,out5,out6,out7)
	model[id].outport.out0 = out0;
	model[id].outport.out1 = out1;
	model[id].outport.out2 = out2;
	model[id].outport.out3 = out3;
	model[id].outport.out4 = out4;
	model[id].outport.out5 = out5;
	model[id].outport.out6 = out6;
	model[id].outport.out7 = out7;
end


--创建新的207模块
function new207(id)
	--调用C接口
	tdevice207_init(id);

	local t = {};
	t.outport0 = {};
	t.outport0.outportval = {out0=false;out1=false;out2=false;out3=false;out4=false;out5=false;out6=false;out7=false};

	t.outport0.mt = {};
	t.outport0.mt.__index = t.outport0.outportval;
	t.outport0.mt.__newindex = function(tb,k,v)
		if(type(v) == "number") then
			if(v == 0) then
				tb.outportval[k] = false;
			else
				tb.outportval[k] = true;
			end

		elseif(type(v) == "boolean") then
			tb.outportval[k] = v;
		end
	end
	setmetatable(t.outport0,t.outport0.mt);

	t.outport1 = {};
	t.outport1.outportval = {out0=false;out1=false;out2=false;out3=false;out4=false;out5=false;out6=false;out7=false};

	t.outport1.mt = {};
	t.outport1.mt.__index = t.outport1.outportval;
	t.outport1.mt.__newindex = function(tb,k,v)
		if(type(v) == "number") then
			if(v == 0) then
				tb.outportval[k] = false;
			else
				tb.outportval[k] = true;
			end

		elseif(type(v) == "boolean") then
			tb.outportval[k] = v;
		end
	end
	setmetatable(t.outport1,t.outport1.mt);

	t.inport0 = {};
	t.inport0.inportval = {in0=false;in1=false;in2=false;in3=false;in4=false;in5=false;in6=false;in7=false};
	t.inport0.mt = {};
	t.inport0.mt.__index = t.inport0.inportval;
	t.inport0.mt.__newindex = function(tb,k,v)
		if(type(v) == "number") then
			if(v == 0) then
				tb.inportval[k] = false;
			else
				tb.inportval[k] = true;
			end

		elseif(type(v) == "boolean") then
			tb.inportval[k] = v;
		end
	end
	setmetatable(t.inport0,t.inport0.mt);

	t.inport1 = {};
	t.inport1.inportval = {in0=false;in1=false;in2=false;in3=false;in4=false;in5=false;in6=false;in7=false};
	t.inport1.mt = {};
	t.inport1.mt.__index = t.inport1.inportval;
	t.inport1.mt.__newindex = function(tb,k,v)
		if(type(v) == "number") then
			if(v == 0) then
				tb.inportval[k] = false;
			else
				tb.inportval[k] = true;
			end

		elseif(type(v) == "boolean") then
			tb.inportval[k] = v;
		end
	end
	setmetatable(t.inport1,t.inport1.mt);

	model[id] = t;
	return t;
end

--
function set207inport(id,in0,in1,in2,in3,in4,in5,in6,in7)
	model[id].inport0.in0 = in0;
	model[id].inport0.in1 = in1;
	model[id].inport0.in2 = in2;
	model[id].inport0.in3 = in3;
	model[id].inport0.in4 = in4;
	model[id].inport0.in5 = in5;
	model[id].inport0.in6 = in6;
	model[id].inport0.in7 = in7;
end

function set207inport2(id,in0,in1,in2,in3,in4,in5,in6,in7)
	model[id].inport1.in0 = in0;
	model[id].inport1.in1 = in1;
	model[id].inport1.in2 = in2;
	model[id].inport1.in3 = in3;
	model[id].inport1.in4 = in4;
	model[id].inport1.in5 = in5;
	model[id].inport1.in6 = in6;
	model[id].inport1.in7 = in7;
end

function set207outport(id,out0,out1,out2,out3,out4,out5,out6,out7)
	model[id].outport0.out0 = out0;
	model[id].outport0.out1 = out1;
	model[id].outport0.out2 = out2;
	model[id].outport0.out3 = out3;
	model[id].outport0.out4 = out4;
	model[id].outport0.out5 = out5;
	model[id].outport0.out6 = out6;
	model[id].outport0.out7 = out7;
end

function set207outport2(id,out0,out1,out2,out3,out4,out5,out6,out7)
	model[id].outport1.out0 = out0;
	model[id].outport1.out1 = out1;
	model[id].outport1.out2 = out2;
	model[id].outport1.out3 = out3;
	model[id].outport1.out4 = out4;
	model[id].outport1.out5 = out5;
	model[id].outport1.out6 = out6;
	model[id].outport1.out7 = out7;
end

function get207outport(id)

	local allbit = 0;
	if(model[id].outport0.out0) then
		allbit = allbit + 1;
	end
	if(model[id].outport0.out1) then
		allbit = allbit + 2;
	end
	if(model[id].outport0.out2) then
		allbit = allbit + 4;
	end
	if(model[id].outport0.out3) then
		allbit = allbit + 8;
	end
	if(model[id].outport0.out4) then
		allbit = allbit + 16;
	end
	if(model[id].outport0.out5) then
		allbit = allbit + 32;
	end
	if(model[id].outport0.out6) then
		allbit = allbit + 64;
	end
	if(model[id].outport0.out7) then
		allbit = allbit + 128;
	end

	return allbit;

end

function get207outport2(id)

	local allbit = 0;
	if(model[id].outport1.out0) then
		allbit = allbit + 1;
	end
	if(model[id].outport1.out1) then
		allbit = allbit + 2;
	end
	if(model[id].outport1.out2) then
		allbit = allbit + 4;
	end
	if(model[id].outport1.out3) then
		allbit = allbit + 8;
	end
	if(model[id].outport1.out4) then
		allbit = allbit + 16;
	end
	if(model[id].outport1.out5) then
		allbit = allbit + 32;
	end
	if(model[id].outport1.out6) then
		allbit = allbit + 64;
	end
	if(model[id].outport1.out7) then
		allbit = allbit + 128;
	end

	return allbit;

end
--

