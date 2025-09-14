namespace Services
{
    interface IFileService<T> where T : class
    {
        public IEnumerable<T> ReadFile(string fileName);
        public void SaveData(IEnumerable<T> data, string fileName);
    }
}
