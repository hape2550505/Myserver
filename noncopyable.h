#pragma once
class noncopyable {//classĬ��private�̳� 
protected:
	noncopyable() {};
		~noncopyable() {};

private:
	noncopyable(const noncopyable&) = delete;
	const noncopyable& operator=(const noncopyable&) = delete;
};