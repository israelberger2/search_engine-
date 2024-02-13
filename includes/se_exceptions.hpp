#ifndef SE_EXCAPTION_HPP
#define SE_EXCAPTION_HPP

#include <stdexcept>


namespace se
{
class BaseExcaption: public std::runtime_error {using std::runtime_error::runtime_error;};

class HtmlExcaption : public BaseExcaption {using BaseExcaption::BaseExcaption;};

class NetworkError : public BaseExcaption {using BaseExcaption::BaseExcaption;};

class SocketError : public BaseExcaption {using BaseExcaption::BaseExcaption;};

class DataError : public BaseExcaption {using BaseExcaption::BaseExcaption;};

class OpenFileError : public BaseExcaption {using BaseExcaption::BaseExcaption;};

class MysqlWordsException : public BaseExcaption {using BaseExcaption::BaseExcaption;};

class InValidWord : public MysqlWordsException {using MysqlWordsException::MysqlWordsException;};

class MysqlLinksExeption : public BaseExcaption {using BaseExcaption::BaseExcaption;};

class InValidLink : public MysqlLinksExeption {using MysqlLinksExeption::MysqlLinksExeption;};

class NoGraph : public BaseExcaption {using BaseExcaption::BaseExcaption;};

class Exit : public BaseExcaption {using BaseExcaption::BaseExcaption;};

}
#endif
