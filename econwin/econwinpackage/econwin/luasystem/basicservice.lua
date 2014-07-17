--基础服务定义

--创建新的定时器函数
function timer(timems)
	local t = {};

	--newtimer
	t.id = newtimer();
	t.PT = timems;--ms
	t.Q =false;--输出信号
	t.INPUT =false;--输入信号
	t.oldIN =false;
	t.setms = function (self,ms)
		self.PT = ms ;
		end
	t.checkin = function (self,input)
		if(input == 0) then
			input = false;
			self.INPUT = input;
		elseif((input == 1)) then
			input = true;
			self.INPUT = input;
		else
			self.INPUT = input;
		end
		if( (not self.oldIN) and (self.INPUT)) then--上升
			--记忆时间点
			starttimer(self.id);
		elseif((self.oldIN) and (self.INPUT)) then--一直为正
			if(timerelapsed(self.id)> self.PT) then
				self.Q = true;
			end
		else
			self.Q = false;
		end

		self.oldIN = self.INPUT;
		end


	return t;
end

--创建新的R_TRIG
function R_TRIG()
	local t = {};

	--newtimer
	t.Q =false;--输出信号
	t.INPUT =false;--输入信号
	t.oldIN =false;

	t.checkin = function (self,input)
		if(input == 0) then
			input = false;
			self.INPUT = input;
		elseif((input == 1)) then
			input = true;
			self.INPUT = input;
		else
			self.INPUT = input;
		end
		if( (not self.oldIN ) and (self.INPUT)) then--上升
			self.Q = true;
		else
			self.Q = false;
		end

		self.oldIN = self.INPUT;
	end


	return t;
end
--创建新的F_TRIG
function F_TRIG()
	local t = {};

	--newtimer
	t.Q = false;--输出信号
	t.INPUT =false;--输入信号
	t.oldIN =false;

	t.checkin = function (self,input)
		if(input == 0) then
			input = false;
			self.INPUT = input;
		elseif((input == 1)) then
			input = true;
			self.INPUT = input;
		else
			self.INPUT = input;
		end
		if( (self.oldIN) and (not self.INPUT)) then--下降沿
			self.Q = true;
		else
			self.Q = false;
		end

		self.oldIN = self.INPUT;
	end


	return t;
end
--用户任务文件注册
--例如:fileregister("usertask1.lua");
filenamelist = {};
filenamelistlen = 0;

function fileregister(filename)
	filenamelist[#filenamelist + 1] = filename;
	filenamelistlen = #filenamelist;
end
