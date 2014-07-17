
keyword={};
keyword["and"] = true;
keyword["break"] = true;
keyword["do"] = true;
keyword["else"] = true;
keyword["elseif"] = true;
keyword["end"] = true;
keyword["false"] = true;
keyword["for"] = true;
keyword["function"] = true;
keyword["if"] = true;
keyword["in"] = true;
keyword["local"] = true;
keyword["nil"] = true;
keyword["not"] = true;
keyword["or"] = true;
keyword["repeat"] = true;
keyword["return"] = true;
keyword["then"] = true;
keyword["true"] = true;
keyword["until"] = true;
keyword["while"] = true;

--全局变量标识
globalvar = {};

--全局变量数组
globalvar2 = {};

--行全局变量
linevar = {};

--全局变量数量
globalvarnum = 0;

--统计行数
lineindex = 1;

--可见的变量及值列表
viewedvar = {};
viewedvarval = {};
viewvarvallen = 0;

fileindex = 0;
--处理文件，生成变量列表
function process(filename)
    --clear
    --globalvar = {};
    --globalvar2 = {};
	fileindex = fileindex + 1;
    linevar[fileindex] = {};
    linevar[fileindex].lineindex = 1;

    --globalvarnum = 0;

    io.input(filename);
    for plineindex=1,math.huge do
        local myst = io.read();
        if(myst == nil) then
			linevar[fileindex].lineindex = plineindex;
            break;
        else
            st = string.gsub(myst,"	","    ");
            --print(st);
            varindex = 0;
            local location = 0;
            local location2 = 0;

            --keyword;
            for i in string.gmatch(st,"%a+[%w:._]*[(]*") do
                if((keyword[i] == nil) and (type(_G[i]) ~= "function") and (type(_G[i]) ~= "userdata") and (type(_G[i]) ~= "table")) then
                    if(string.find(i,"[(]") == nil) then
                    location,location2 = string.find(st,i,location+1);


                    if(globalvar[i] == nil) then
                            globalvar[i] = i;

                            globalvarnum = globalvarnum + 1;
                            globalvar2[globalvarnum] = {};
                            globalvar2[globalvarnum].name = i;
                            --print(getfieldtype(i));
                            if(getfieldtype(i) == "number") then
                                globalvar2[globalvarnum].t = 0;
                            elseif(getfieldtype(i) == "boolean" or getfieldtype(i) == "nil") then
                                globalvar2[globalvarnum].t = 1;
                            else
                                globalvar2[globalvarnum].t = 0;
                            end
                        end

                            --globalvar2[globalvarnum].t = type(i);

                            linevar[fileindex].lineindex = plineindex;

                            varindex = varindex + 1;
                            --print(lineindex,varindex);

                            if(linevar[fileindex][plineindex]== nil) then
                                linevar[fileindex][plineindex] = {};
                                linevar[fileindex][plineindex].len = varindex;
                                linevar[fileindex][plineindex][varindex] = {};
                                linevar[fileindex][plineindex][varindex].name = i;
                                linevar[fileindex][plineindex][varindex].location = (location + location2)/2;
                            else
                                linevar[fileindex][plineindex].len = varindex;
                                linevar[fileindex][plineindex][varindex] = {};
                                linevar[fileindex][plineindex][varindex].name = i;
                                linevar[fileindex][plineindex][varindex].location = (location + location2)/2;
                            end
                            --print(plineindex,linevar[fileindex][plineindex][varindex].name,linevar[fileindex][plineindex][varindex].location,linevar[fileindex][plineindex].len);
                        --end
                    --print(i);
                    end
                end
            end

        end
    end
end


function getfield(f)
    local v= _G;
    for w in string.gmatch(f,"[%w_]+") do
        if(v[w] ~= nil) then
        v = v[w];
        else
            return nil;
        end
    end
    return v;
end

function getfieldtype(f)
    local v= _G;
    for w in string.gmatch(f,"[%w_]+") do
        if(v[w] ~= nil) then
        v = v[w];
        else
            return nil;
        end
    end
    return type(v);
end

function viewvar()
    for i in pairs(globalvar) do
        print(globalvar[i],getfield(globalvar[i]));
    end
    print("--------------------------------------------");
    for i,v in pairs(globalvar2) do
        print(v.name,v.t);
    end
end

function  freshviewedvar(fileid,beginline,endline)

    viewedvar = {};
    viewedvarval = {};
    viewvarvallen = 1;

    for i=beginline,endline do
        if(linevar[fileid][i] ~= nil) then
            for ii = 1,linevar[fileid][i].len do
                if(viewedvar[linevar[fileid][i][ii].name] == nil) then

                    viewedvar[linevar[fileid][i][ii].name] = linevar[fileid][i][ii].name;
                    viewedvarval[viewvarvallen] = {};
                    viewedvarval[viewvarvallen].name = linevar[fileid][i][ii].name;
                    viewedvarval[viewvarvallen].val = getfield(linevar[fileid][i][ii].name);
                    --print(viewedvarval[viewvarvallen].name,viewedvarval[viewvarvallen].val);
                    viewvarvallen = viewvarvallen + 1;
                end
            end
        end
    end
end

function  freshviewedvarval()
    for i = 1,#viewedvarval do
        viewedvarval[i].val = getfield(viewedvarval[i].name);
        --print(viewedvarval[i].name,viewedvarval[i].val);
    end
end

--num = 2;
--print(type(num));
--process("./usertask.lua");
--freshviewedvar();
--viewvar();

--print(string.gmatch("hehehehe  hehehe hehehe ","he"));
--print(st);
