#include "value_map.h"
#include <iostream>
#include <algorithm>
#include <Windows.h>

namespace bootleg {
	//--------------------------------------------------
	template <class T>
	std::unique_ptr<value_map<T>> value_map<T>::create()
	{
		return std::make_unique<value_map<T>>();
	}
	//--------------------------------------------------
	template <class T>
	std::vector<T> * value_map<T>::unfiltered_values()
	{
		return &m_UnfilteredValues;
	}
	//--------------------------------------------------
	template <class T>
	std::vector<T> * value_map<T>::discarded_values()
	{
		return &m_DiscardedValues;
	}
	//--------------------------------------------------
	template <class T>
	bool value_map<T>::is_new_value(T val)
	{
		// We only need to check m_DiscardedValues.
		// This is because m_UnfilteredValues is filtered prior to being added to m_DiscardedValues.
		for (auto& i : m_DiscardedValues) {
			if (i == val)
				return false;
		}
		return true;
	}
	//--------------------------------------------------
	template <class T>
	void value_map<T>::print_unfiltered_values()
	{
		for (auto& i : m_UnfilteredValues) {
			printf("%d ", i);
		}
		printf("\n");
	}
	//--------------------------------------------------
	template <class T>
	void value_map<T>::filter_duplicates()
	{
		// std::unique removes consecutive duplicate values, so sorting is needed.
		std::sort( m_UnfilteredValues.begin(), m_UnfilteredValues.end() );
		typename std::vector<SillyTemplateType>::iterator it;
		it = std::unique( m_UnfilteredValues.begin(), m_UnfilteredValues.end() );
		m_UnfilteredValues.resize( std::distance(m_UnfilteredValues.begin(), it) );
	}
	//--------------------------------------------------
	template <class T>
	void value_map<T>::discard_all()
	{
		// Filter the values in m_Unfiltered
		this->filter_duplicates();
		// Append filtered m_UnfilteredValues to m_DiscardedValues
		m_DiscardedValues.insert( m_DiscardedValues.end(), m_UnfilteredValues.begin(), m_UnfilteredValues.end() );
		// Clear out m_UnfilteredValues.
		m_UnfilteredValues.clear();
	}
	//--------------------------------------------------
	template <class T>
	void value_map<T>::push(T value)
	{
		if (this->is_new_value(value)) {
			m_UnfilteredValues.push_back(value);
		}
	}
	// I don't like this. Is there a better way?
	template class value_map<int>;
}

