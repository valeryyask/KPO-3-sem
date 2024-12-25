#include "stdafx.h"

namespace IT
{
	IdTable::IdTable()
	{
		this->noname_lexema_count = 0;
		this->maxsize = TI_MAXSIZE;
		this->size = 0;
		this->table = new Entry[TI_MAXSIZE];
	}
	Entry::Entry()
	{
		this->parrent_function[0] = '\0';
		this->id[0] = '\0';
		this->firstApi = 0;
		this->iddatatype = IT::IDDATATYPE::DEF;
		this->idtype = IT::IDTYPE::D;
		this->parmQuantity = 0;

	}

	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, int it)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		this->value.vint = it;
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, char* ch)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		strcpy_s(this->value.vstr.str, 255, ch);
		this->value.vstr.len = strlen(ch);
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, const char* ch)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		strcpy_s(this->value.vstr.str, 255, ch);
		this->value.vstr.len = strlen(ch);
	}
	Entry::Entry(char* parrent_function, char* id, IDDATATYPE iddatatype, IDTYPE idtype)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
	}

	IdTable Create(int size)
	{
		IdTable id_table;
		id_table.size = size;
		id_table.maxsize = TI_MAXSIZE;
		id_table.table = new Entry[TI_MAXSIZE];
		return id_table;
	}
	void IdTable::Add(Entry entry)
	{
		if (strlen(entry.id) > ID_MAXSIZE && entry.idtype != IDTYPE::F)
			throw ERROR_THROW(121);

		if (this->size < this->maxsize)
		{
			if (entry.idtype != IDTYPE::F)
				entry.id[5] = '\0';
			this->table[this->size] = entry;

			switch (entry.iddatatype)
			{
			case IDDATATYPE::INT:
			{
				this->table[this->size].value.vint = TI_INT_DEFAULT;
			}
			case IDDATATYPE::STR:
			{
				this->table[this->size].value.vstr.str[0] = TI_STR_DEFAULT;
				this->table[this->size].value.vstr.len = 0;
			}
			}
			this->size++;
		}
		else
			throw ERROR_THROW(122);

	}
	Entry IdTable::GetEntry(int n)
	{
		if (n < this->size && n >= 0)
			return this->table[n];
	}
	int IdTable::IsId(const char id[ID_MAXSIZE])
	{
		for (int iter = 0; iter < this->size; iter++)
		{
			if (strcmp(this->table[iter].id, id) == 0)
				return iter;
		}
		return TI_NULLIDX;
	}
	int IdTable::IsId(const char id[ID_MAXSIZE], const char parrent_function[ID_MAXSIZE + 5])
	{
		for (int i = 0; i < this->size; i++)
		{
			if ((strcmp(this->table[i].id, id) == 0) &&
				(strcmp(this->table[i].parrent_function, parrent_function) == 0))
				return i;
		}
		return TI_NULLIDX;
	}
	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
		idtable.table = nullptr;
	}

	char* IdTable::GetLexemaName()
	{
		char buffer[3];
		char tempBuf[5];
		_itoa_s(this->noname_lexema_count, buffer, 10);
		tempBuf[0] = 'L';
		tempBuf[1] = '_';
		tempBuf[2] = buffer[0];
		tempBuf[3] = buffer[1];
		tempBuf[4] = buffer[2];
		return tempBuf;
	}

	void IdTable::PrintIdTable(const wchar_t* in)
	{

		bool flagForFirst = false;
		char buffer[3];
		char tempBuf[5];
		int lexema_count = 0;
		bool exist = true;
		tempBuf[0] = 'L';
		tempBuf[1] = '_';

		cout << "\nТаблица идентификаторов" << std::endl;

		for (int i = 0; i < this->size; i++)
		{
			switch (this->table[i].idtype)
			{
			case IT::IDTYPE::V:
				switch (this->table[i].iddatatype)
				{
				case 1://10
					cout << "TypeOfId: " << "Переменная" << "\t" << "id: " << this->table[i].id << " " << "\t" << "dataType: " << "INT " << "value: " << 0 << " " << "idxFirstLE: " << this->table[i].firstApi << std::endl;
					break;
				case 2:
					cout << "TypeOfId: " << "Переменная" << "\t" << "id: " << this->table[i].id << " " << "\t" << "dataType: " << "STR " << "value: " << "\"\" " << "idxFirstLE: " << this->table[i].firstApi << std::endl;
					break;
				}
				break;


			case IT::IDTYPE::P:
				switch (this->table[i].iddatatype)
				{
				case 1://8
					cout << "TypeOfId: " << "Параметр" << "\t" << "id: " << this->table[i].id << " " << "\t" << "dataType: " << "INT " << "value: " << 0 << " " << "idxFirstLE: " << this->table[i].firstApi << std::endl;
					break;
				case 2:
					cout << "TypeOfId: " << "Параметр" << "\t" << "id: " << this->table[i].id << " " << "\t" << "dataType: " << "STR " << "value: " << "\"\" " << "idxFirstLE: " << this->table[i].firstApi << std::endl;
					break;
				}
				break;

			case IT::IDTYPE::L:
				_itoa_s(lexema_count, buffer, 10);

				exist = false;

				tempBuf[2] = buffer[0];
				tempBuf[3] = buffer[1];
				tempBuf[4] = buffer[2];
				switch (this->table[i].iddatatype)
				{
				case 1://7
					for (int k = 0; k < i; k++) {
						if (this->table[k].idtype == IT::IDTYPE::L)
							if (this->table[k].value.vint == this->table[i].value.vint) {
								exist = true;
								break;
							}
					}
					if (!exist) {
						cout << "TypeOfId: " << "Литерал" << "\t" << tempBuf << " " << "\t" << "dataType: " << "INT " << "value: " << this->table[i].value.vint << " " << "idxFirstLE: " << this->table[i].firstApi << std::endl;
						lexema_count++;
					}
					break;
				case 2:
					for (int k = 0; k < i; k++) {
						for (int j = 0; j < 10; j++) {
							if (this->table[k].idtype == IT::IDTYPE::L)
								if (this->table[k].value.vstr.str[j] != this->table[i].value.vstr.str[j]) {
									exist = false;
									break;
								}
							exist = true;
						}
					}
					if (!exist) {
						cout << "TypeOfId: " << "Литерал" << "\t" << tempBuf << " " << "\t" << "dataType: " << "STR " << "value: " << this->table[i].value.vstr.str << " " << "idxFirstLE: " << this->table[i].firstApi << std::endl;
						lexema_count++;
					}
					break;
				}
				break;
			case IT::IDTYPE::F:
				switch (this->table[i].iddatatype)
				{
				case 1://7
					cout << "TypeOfId: " << "Функция" << "\t" << "id: " << this->table[i].id << "\t" << "dataType: " << "INT " << "value: " << "- " << "idxFirstLE: " << this->table[i].firstApi << " " << "Parms:" << this->table[i].parmQuantity << std::endl;
					break;
				case 2:
					cout << "TypeOfId: " << "Функция" << "\t" << "id: " << this->table[i].id << "\t" << "dataType: " << "STR " << "value: " << "- " << "idxFirstLE: " << this->table[i].firstApi << " " << "Parms:" << this->table[i].parmQuantity << std::endl;
					break;
				}
				break;


			}
		}




		/*

						if (this->table[i].idtype == IT::IDTYPE::V)
			{


				switch (this->table[i].iddatatype)
				{
				case 1:
				{
					*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "INT " << "V" << "   " << this->table[i].firstApi << std::endl;
					break;
				}
				case 2:
				{
					*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "STR " << "V" << "   " << this->table[i].firstApi << std::endl;
					break;
				}
				}

				flagForFirst = true;
			}

			if (this->table[i].idtype == IT::IDTYPE::P)
			{

				switch (this->table[i].iddatatype)
				{
				case 1:
				{
					*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "INT " << "P" << "   " << this->table[i].firstApi << std::endl;
					break;
				}
				case 2:
				{
					*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "STR " << "P" << "   " << this->table[i].firstApi << std::endl;
					break;
				}
				}

				flagForFirst = true;
			}


		switch (this->table[i].iddatatype)
					{
						case 1:
							*(idStream) << "   " << this->table[i].id << "   " << "INT " << "  " << 0 << "       " << this->table[i].firstApi << std::endl;
							break;
						case 2:
							*(idStream) << "   " << this->table[i].id << "   " << "STR " << "     " << "    \"\"" << "       " << this->table[i].firstApi << std::endl;
							break;
					}
					break;



		* (idStream) << "\n\n\n";
#pragma region Functions

			flagForFirst = false;

			*(idStream) << "------------------ Функции ------------------" << std::endl;

			*(idStream) << "Идентификатор:" << std::setw(26) << "Тип данных возврата:" << std::setw(36) << "Количество переданных параметров:" << std::setw(22) << "Первое вхождение:" << std::endl;


								case IT::I

								case IT::IDTYPE::V:
						switch (this->table[i].iddatatype)
						{
							case 1:
								*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "INT " << "V" << "   " << this->table[i].firstApi << std::endl;
								break;
							case 2:
								*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "STR " << "V" << "   " << this->table[i].firstApi << std::endl;
								break;
						}
						flagForFirst = true;
						break;


#pragma endregion
			* (idStream) << "\n\n\n";
#pragma region Variables

			flagForFirst = false;

			*(idStream) << "------------------ Переменные ------------------" << std::endl;
			*(idStream) << std::setw(25) << "Имя родительского блока:" << std::setw(20) << "Идентификатор:" << std::setw(16) << "Тип данных:" << "Тип идентификатора:" << std::setw(21) << "Первое вхождение:" << std::endl;

			for (int i = 0; i < this->size; i++)
			{


			}
*/

	}
}