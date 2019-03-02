#include "memberrepo.h"

MemberRepo::MemberRepo()
{

}

Member* MemberRepo::findByMemberID(int memberID)
{
    QSqlQuery* resultSet = dbUtil->query("select * from member_info where id=" +
                                         to_string(memberID) + ";");
    Member* member = NULL;
    while(resultSet->next()) {
        member = new Member(resultSet->value(0).toInt());
    }
    delete resultSet;
    return member;
}

void MemberRepo::saveMember(Member* &member)
{
    dbUtil->execute("insert into member_info values(" +
                    to_string(member->id) + ");");
}
