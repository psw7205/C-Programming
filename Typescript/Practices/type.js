"use strict";
// var 호이스팅 O
// let, const 호이스팅 X
// const를 기본적으로 쓰고, 재할당이 반드시 필요한 변수만 let을 이용해 선언
// 변수 타입: number, string, boolean
// let<변수명>: <타입명> = <값>;
var num = 1;
console.log("num :", num);
var str = "string";
console.log("str :", str);
//[](array)
var arrNum = [1, 2, 3];
var strNum = ["ABC", "DEF", "EFG"];
console.log("arrNum :", arrNum);
console.log("strNum :", strNum);
//tuple
var tup = [25, "박상우"];
console.log("tuple :", tup);
// any 어느 자료형이든 할당 가능, 타입검사 X
var item = 1;
item = true;
item = "string";
// void 함수 반환 시 값이 없는 경우
// null, undefined
// 유니온 타입
var val; //number 또는 string타입 할당 가능
val = 1;
val = "string";
// enum
var Color;
(function (Color) {
    Color[Color["Red"] = 0] = "Red";
    Color[Color["Green"] = 1] = "Green";
    Color[Color["Blue"] = 2] = "Blue";
})(Color || (Color = {}));
var color = Color.Green;
