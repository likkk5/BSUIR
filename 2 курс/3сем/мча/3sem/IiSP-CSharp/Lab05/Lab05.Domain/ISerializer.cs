namespace Lab05.Domain
{
    public interface ISerializer
    {
        IEnumerable<Airoport> DeSerializeByLINQ(string fileName);
        IEnumerable<Airoport> DeSerializeXML(string fileName);
        IEnumerable<Airoport> DeSerializeJSON(string fileName);

        void SerializeByLINQ(IEnumerable<Airoport> list, string fileName);
        void SerializeXML(IEnumerable<Airoport> list, string fileName);
        void SerializeJSON(IEnumerable<Airoport> list, string fileName);

    }
}