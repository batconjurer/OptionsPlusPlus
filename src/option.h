#include <stdexcept>
#include <iostream>

namespace Options {
enum opt_val {
	Some,
	None
};

template <class Type>
class Option {
private: 
	opt_val valid;
	Type* val;
	bool is_none() const;

public:
	Option();
	Option(const opt_val& other);
	Option(Type &value);
	Option(Type *value);
	Type get() const;
	bool operator==(const Option &rhs_opt);
	bool operator!=(const Option &rhs_opt);
	bool operator==(const opt_val &val);
	bool operator!=(const opt_val &val);
	Option<Type>& operator=(const Option<Type>& other){
		return Option<Type>(other.val);
	}

	Option<Type>& operator=(const opt_val& other);
	Option<Type>& operator=(const Type& other);

};

template <class Type>
Option<Type>& Option<Type>::operator=(const opt_val& other){
		if (other == Some){
			throw std::runtime_error("Cannot set type Option to Some explicilty; must be intialized with an object instance");
		} else {
			this->valid = None;
			this->val = nullptr;
		}
		return *this;
}

template <class Type>
Option<Type>& Option<Type>::operator=(const Type& other){
	this->valid = Some;
	this->val = other;
	return *this;
}

template <class Type>
Option<Type>::Option(){
	val = nullptr;
	valid = None;
}

template <class Type>
Option<Type>::Option(const opt_val& other){
	if (other == Some){
		throw std::runtime_error("Cannot set type Option to Some explicilty; must be intialized with an object instance");
	} else {
		valid = None;
		val = nullptr;
	}
}

template <class Type>
Option<Type>::Option(Type &value){
	valid = Some;
	val = &value;
}

template <class Type>
Option<Type>::Option(Type *value){
	if (value == nullptr){
		valid = None;
	} else {
		valid = Some;
	}
	val = value;
}

template <class Type>
bool Option<Type>::is_none() const {
	if (valid == None) {
		return true;
	} else {
		return false;
	}
}

// Warning! Not a safe method. Hence is static so not accessible from outside.
template <class Type>
Type Option<Type>::get() const {
	if (val == nullptr) {
		throw std::runtime_error("None type has no value");
	}
	return *(val);
}


template <class Type>
bool Option<Type>::operator==(const Option<Type> &rhs_opt) {
	if (this->is_none() && rhs_opt.is_none()){
		return true;
	} else if (!this->is_none() && !rhs_opt.is_none()){
		return this->get() == rhs_opt.get();
	} else {
		return false;
	}
}

template <class Type>
bool Option<Type>::operator!=(const Option<Type> &rhs_opt){
	return !(*this == rhs_opt);
}

template <class Type>
bool Option<Type>::operator==( const opt_val &val) {
	return this->valid == val;
}

template <class Type>
bool Option<Type>::operator!=(const opt_val &val) {
	return !(this->valid == val);
}


};